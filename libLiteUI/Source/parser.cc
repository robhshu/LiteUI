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
  parser_helper( parser &parser_ref )
    : m_parser( parser_ref )
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

      for( XMLNode *pNode = pRoot->FirstChild(); pNode != nullptr; pNode = pNode->NextSibling() ) {
        const string szNodeType = pNode->Value();
        element *pEle = m_parser.OnCreateElement(szNodeType);

        if( szNodeType == "group" ) {

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

      m_parser.GetSceneGraph().AddScene(pScene);
      return true;
    } else {
      return false;
    }
  }

  bool LoadGroup( XMLElement *pRoot, group *pOwner )
  {
    for( XMLNode *pNode = pRoot->FirstChild(); pNode != nullptr; pNode = pNode->NextSibling() ) {
      const string szNodeType = pNode->Value();
      element *pEle = m_parser.OnCreateElement(szNodeType);

      if( !pEle ) {
        // unable to create element
        return false;
      }

      const XMLElement *pElement = pNode->ToElement();
      for( const XMLAttribute *pAttrib = pElement->FirstAttribute(); pAttrib != nullptr; pAttrib = pAttrib->Next() ) {
        //int value = 0;
        //if( pAttrib->QueryIntValue(&value) == tinyxml2::XML_SUCCESS ) {
        //  pEle->SetProperty(pAttrib->Name(), value);
        //} else {
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

      pOwner->AddChild(pEle);
    }

    return true;
  }

};

parser::parser( scenegraph &sgRef )
  : m_scenegraph( sgRef )
{
}

bool parser::Read( const string &szXML )
{
  parser_helper xmlParser(*this);

  return xmlParser.Serialize( szXML );
}

scene *parser::OnCreateScene( ) const
{
  return new scene;
}

element *parser::OnCreateElement( const string &szType ) const
{
  #define MAKE_ELEMENT_FROM_TYPE(t) if( szType.compare(#t) == 0 ) { return new t; }
  MAKE_ELEMENT_FROM_TYPE(group);
  MAKE_ELEMENT_FROM_TYPE(button);
  MAKE_ELEMENT_FROM_TYPE(label);
  MAKE_ELEMENT_FROM_TYPE(panel);
  #undef MAKE_ELEMENT_FROM_TYPE

  return nullptr;
}

scenegraph &parser::GetSceneGraph( )
{
  return m_scenegraph;
}

};
