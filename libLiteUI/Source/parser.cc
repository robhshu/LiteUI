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

#include <json/reader.h>
#include <sstream>

#include <windows.h>

namespace liteui
{
class parser_helper
{
public:
  parser_helper( parser &parser_ref )
    : m_parser( parser_ref )
  {
  }

  bool Serialize( const string& szJson )
  {
    json::Object jsonRoot;

    if( !CanSerialize( szJson, jsonRoot ) ) {
      return false;
    }
  
    if( jsonRoot.Empty() ) {
      return false;
    }

    return ParseScene(jsonRoot);
  }

private:
  parser &m_parser;

  static bool CanSerialize( const string &szJson, json::Object &jsonRoot )
  {
    std::istringstream jsonString(szJson);

    try {
      json::Reader::Read(jsonRoot, jsonString);
    } catch( json::Reader::ParseException& ) {
      return false;
    }

    return true;
  }

  bool ParseElement( base *pOwner, const json::Object &jsonObject )
  {
    for( json::Object::const_iterator citNode = jsonObject.Begin(); citNode != jsonObject.End(); citNode++ ) {
      
      const char typeHint = citNode->name[0];

      if( typeHint == '@' ) {
        // string properties

        const json::String &str = citNode->element;
        pOwner->SetProperty(citNode->name.substr(1), str.Value());
      } else if( typeHint == '^' ) {
        // integer properties

        const json::Number &num = citNode->element;
        pOwner->SetProperty(citNode->name.substr(1), static_cast<unsigned >( num.Value() ));
      } else {
        // hopefully an element namae

        element *pEle = m_parser.OnCreateElement(citNode->name);
        if( pEle ) {
          const json::Array &jsonNode = citNode->element;

          if( !ParseElement( pEle, *jsonNode.Begin() ) ) {
            // not an element, so unknown
            return false;
          }

          if( pOwner->GetTypeName() == "scene" && pEle->GetTypeName() == "group" ) {
            static_cast<scene* >(pOwner)->AddGroup( static_cast<group *>( pEle ) );
          } else if( pOwner->GetTypeName() == "group" ) {
            static_cast<group* >( pOwner )->AddChild( pEle );
          } else {
            // we cannot parent this element !
            delete pEle;
            return false;
          }

        } else {
          // failed to create
          return false;
        }
      }
    }

    return true;
  }

  bool ParseScene( const json::Object &jsonRoot )
  {
    const string scene_type("scene");

    for( json::Object::const_iterator citRoot = jsonRoot.Begin(); citRoot != jsonRoot.End(); citRoot++ ) {
      if( citRoot->name == scene_type ) {
        scene *pScene = m_parser.OnCreateScene();

        if( !pScene ) {
          // creation failure (virtual call may be wrong)
          return false;
        }

        const json::Array &jsonNode = citRoot->element;

        if( !ParseElement(pScene, *jsonNode.Begin()) ) {
          // something went wrong

          delete pScene;
          pScene = nullptr;

          return false;
        }

        // add scene to scenegraph
        m_parser.GetSceneGraph().AddScene( pScene );

      } else {
        // expected scene def
        return false;
      }
    }

    return true;
  }
};

parser::parser( scenegraph &sgRef )
  : m_scenegraph( sgRef )
{
}

bool parser::Read( const string &szJson )
{
  parser_helper jsonParser(*this);

  return jsonParser.Serialize( szJson );
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
