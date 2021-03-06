//
//  liteui::parser
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#include <liteui/parser.h>

#include <liteui/scene.h>
#include <liteui/group.h>
#include <liteui/button.h>
#include <liteui/label.h>
#include <liteui/panel.h>

#include "tinyxml2.h"

namespace liteui
{
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using tinyxml2::XMLNode;
using tinyxml2::XMLAttribute;

class parser_helper
{
public:
  parser_helper( parser &parser_ref, scenegraph &sgRef )
    : m_sceneGraph( sgRef )
    , m_parser( parser_ref )
  {
  }

  bool Serialize( const string& szXML )
  {
    XMLDocument xmlDoc;

    if( CanSerialize( szXML, xmlDoc ) ) {
      return LoadScene( xmlDoc.RootElement() );
    }

    xmlDoc.Clear();
    return false;
  }

private:
  scenegraph &m_sceneGraph;
  parser &m_parser;

  static bool CanSerialize( const string &szXML, XMLDocument &xmlDoc )
  {
    tinyxml2::XMLError xmlError = xmlDoc.Parse(szXML.c_str(), szXML.length());
    return xmlError == tinyxml2::XML_SUCCESS;
  }

  bool LoadScene( XMLElement* pRoot )
  {
    const string szScene = "scene";
    if( szScene == pRoot->Value() ) {
      scene *pScene = m_parser.OnCreateScene();
      if( pScene == nullptr ) {
        return false;
      }

      // try to name scene (todo: default to filename)
      XMLElement *pAsElement = pRoot->ToElement();

      if( pAsElement ) {
        for( const XMLAttribute *pAttrib = pAsElement->FirstAttribute(); pAttrib != nullptr; pAttrib = pAttrib->Next() ) {
          if( pAttrib->Name() == string("name") ) {
            pScene->SetName(pAttrib->Value());
          }
        }
      }

      for( XMLNode *pNode = pRoot->FirstChild(); pNode != nullptr; pNode = pNode->NextSibling() ) {
        // Skip comments
        if( pNode->ToComment() ) {
          continue;
        }

        const string szNodeType = pNode->Value();
        if( szNodeType == "group" ) {
          element *pEle = m_parser.OnCreateElement(szNodeType);
          if( !pEle ) {
            // unable to create group
            return false;
          }

          if( !LoadAttributes( pNode->ToElement(), pEle ) ) {
            pEle->Release( );
            return false;
          }

          if( LoadGroup( pNode->ToElement(), static_cast<group*>(pEle) ) ) {
            pScene->AddGroup( static_cast<group*>(pEle) );
          } else {
            // failed to load group
            pScene->Release();
            return false;
          }          
        } else {
          // cannot add anything but a group to this scene

          pScene->Release();
          return false;
        }
      }

      m_sceneGraph.AddScene(*pScene);
      return true;
    } else {
      return false;
    }
  }

  bool LoadGroup( XMLElement *pRoot, group *pOwner )
  {
    for( XMLNode *pNode = pRoot->FirstChild(); pNode != nullptr; pNode = pNode->NextSibling() ) {
      // Skip comments
      if( pNode->ToComment() ) {
        continue;
      }

      element *pEle = m_parser.OnCreateElement(pNode->Value());

      if( !pEle ) {
        // unable to create element
        return false;
      }

      if( !LoadAttributes( pNode->ToElement(), pEle ) ) {
        pEle->Release( );
        return false;
      }

      if(pEle->GetTypeName()=="group") {

        if( LoadGroup( pNode->ToElement(), static_cast<group*>(pEle) ) ) {
          pOwner->AddGroup(static_cast<group*>(pEle));
        } else {
          pEle->Release();
          return false;
        }
      } else {
        pOwner->AddChild(pEle);
      }
    }

    return true;
  }

  bool LoadAttributes( XMLElement *pElement, element *pEle )
  {
    for( const XMLAttribute *pAttrib = pElement->FirstAttribute(); pAttrib != nullptr; pAttrib = pAttrib->Next() ) {
      if( pAttrib->Name() == string("text") ) {
        static_cast<label* >(pEle)->SetText( pAttrib->Value() );
      } else if( pAttrib->Name() == string("onFocus") ) {
        pEle->SetEventReason(element_callback_reason::cb_focus, pAttrib->Value());
      } else if( pAttrib->Name() == string("onBlur") ) {
        pEle->SetEventReason(element_callback_reason::cb_blur, pAttrib->Value());
      } else if( pAttrib->Name() == string("onPress") ) {
        pEle->SetEventReason(element_callback_reason::cb_press, pAttrib->Value());
      } else if( pAttrib->Name() == string("onRelease") ) {
        pEle->SetEventReason(element_callback_reason::cb_release, pAttrib->Value());
      } else {
        pEle->SetProperty( pAttrib->Name(), pAttrib->Value() );
      }
    }

    return true;
  }
};

bool parser::LoadSceneGraph( scenegraph &sgRef, const string &szXML )
{
  parser_helper xmlParser(*this, sgRef);

  return xmlParser.Serialize( szXML );
}

scene *parser::OnCreateScene( )
{
  scene *pScene = new scene;

  pScene->IncReferenceCount();

  return pScene;
}

element *parser::OnCreateElement( const string &szType )
{
  element *pEle = nullptr;

  if( szType == "group" ) {
    pEle = new group;
  } else if( szType == "button" ) {
    pEle = new button;
  } else if( szType == "label" ) {
    pEle = new label;
  } else if( szType == "panel" ) {
    pEle = new panel;
  }

  if( pEle ) {
    pEle->IncReferenceCount( );
  }

  return pEle;
}

};
