//
//  liteui::parser
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_PARSER_H
#define LIBLITEUI_PARSER_H

#include <liteui/common.h>
#include <liteui/element.h>
#include <liteui/scenegraph.h>

namespace liteui
{
class parser
{
public:
  /// Parse an XML string and load into an existing scenegraph
  bool LoadSceneGraph( scenegraph &sgRef, const string &szXML );

  /// Request a scene be created when parsing XML 
  virtual scene *OnCreateScene( );

  /// Request an element be created by name when parsing XML
  virtual element *OnCreateElement( const string &szType );
};
};

#endif
