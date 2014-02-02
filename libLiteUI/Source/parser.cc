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

namespace liteui
{
bool CanSerialize( const string &szJson, json::Object &jsonRoot )
{
  std::istringstream jsonString(szJson);

  try {
    json::Reader::Read(jsonRoot, jsonString);
  } catch( json::Reader::ParseException& ) {
    return false;
  }

  return true;
}

bool ParseElement( parser *pThis, scene *pScene, const json::Array &jsonArray )
{


    //citRoot->

    //if( citRoot->name[0] == '@' ) {
    //  // internal property (lookup somewhere)
    //  OutputDebugStringA(citRoot->name.c_str());
    //  
    //} else {
    //  // possibly another element
    //  if( !ParseElement( pThis, pScene, citRoot->element ) ) {
    //    // not an element, so unknown
    //    return false;
    //  }
    //}

  return false;
}

bool ParseScene( parser *pThis, const json::Object &jsonRoot )
{
  const string scene_type("scene");

  for( json::Object::const_iterator citRoot = jsonRoot.Begin(); citRoot != jsonRoot.End(); citRoot++ ) {
    if( citRoot->name == scene_type ) {
      scene *pScene = pThis->OnCreateScene();

      if( !pScene ) {
        // creation failure (virtual call may be wrong)
        return false;
      }

      if( !ParseElement(pThis, pScene, citRoot->element) ) {
        // something went wrong
        return false;
      }
    } else {
      // expected scene def
      return false;
    }
  }

  return true;
}

bool parser::Read( const string &szJson )
{
  json::Object jsonRoot;

  if( !CanSerialize( szJson, jsonRoot ) ) {
    return false;
  }
  
  if( jsonRoot.Empty() ) {
    return false;
  }

  return ParseScene(this, jsonRoot);
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

};
