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
      scene::uptr sceneinst(m_parser.OnCreateScene());

      if (sceneinst == nullptr) {
        return false;
      }

      // try to name scene (todo: default to filename)
      XMLElement *pAsElement = pRoot->ToElement();

      if( pAsElement ) {
        for( const XMLAttribute *pAttrib = pAsElement->FirstAttribute(); pAttrib != nullptr; pAttrib = pAttrib->Next() ) {
          if( pAttrib->Name() == string("name") ) {
            sceneinst->SetName(pAttrib->Value());
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

          group::inst grouprawptr(reinterpret_cast<group*>(m_parser.OnCreateElement(szNodeType)));
          group::uptr groupinst(grouprawptr);

          if (!groupinst) {
            // unable to create group
            return false;
          }

          // automatically downcast to element
          if (!LoadAttributes(pNode->ToElement(), groupinst.get())) {
            return false;
          }

          if (LoadGroup(pNode->ToElement(), groupinst )) {
            group::ptr groupptr(groupinst.release());
            sceneinst->AddGroup(groupptr);
          } else {
            // failed to load group
            return false;
          }          
        } else {
          // cannot add anything but a group to this scene

          return false;
        }
      }

      // XXX revisit this too
      m_sceneGraph.AddScene(*sceneinst.release());
      return true;
    } else {
      return false;
    }
  }

  bool LoadGroup( XMLElement *pRoot, const group::uptr &groupowner )
  {
    for( XMLNode *pNode = pRoot->FirstChild(); pNode != nullptr; pNode = pNode->NextSibling() ) {
      // Skip comments
      if( pNode->ToComment() ) {
        continue;
      }

      const std::string elementname(pNode->Value());
      element * meh = m_parser.OnCreateElement(elementname);

      element::uptr elementinst(meh);

      if (!elementinst) {
        // unable to create element
        return false;
      }

      if (!LoadAttributes(pNode->ToElement(), elementinst.get())) {
        return false;
      }

      if (elementinst->GetTypeName() == "group") {
        group::uptr groupinst(reinterpret_cast<group*>(elementinst.release()));

        if (LoadGroup(pNode->ToElement(), groupinst) ) {
          group::ptr groupptr(groupinst.release());
          groupowner->AddGroup(groupptr);
        } else {
          return false;
        }
      } else {
        element::ptr elementptr(elementinst.release());
        groupowner->AddChild(elementptr);
      }
    }

    return true;
  }

  bool LoadAttributes( XMLElement *pElement, element *pEle )
  {
    for( const XMLAttribute *pAttrib = pElement->FirstAttribute(); pAttrib != nullptr; pAttrib = pAttrib->Next() ) {
      if( pAttrib->Name() == string("text") ) {
        // odd.
        dynamic_cast<label* >(pEle)->SetText( pAttrib->Value() );
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
  
  return pScene;
}

element *parser::OnCreateElement( const string &szType )
{
  element *pEle = nullptr;

  if( szType == "group" ) {
    pEle = new group();
  } else if( szType == "button" ) {
    pEle = new button();
  } else if( szType == "label" ) {
    pEle = new label();
  } else if( szType == "panel" ) {
    pEle = new panel();
  }

  return pEle;
}

};
