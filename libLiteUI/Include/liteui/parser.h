//
//  liteui::parser
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_PARSER_H
#define LIBLITEUI_PARSER_H

#include <liteui/scene.h>
#include <liteui/element.h>
#include <liteui/scenegraph.h>

namespace liteui
{
class parser
{
public:
  /// Default constructor; an existing scenegraph must be supplied by reference
  parser( scenegraph &sgRef );

  /// Parse an XML string and load into the scenegraph
  bool Read( const string &szXML );

  /// Request a scene be created when parsing XML 
  virtual scene *OnCreateScene( ) const;

  /// Request an element be created by name when parsing XML
  virtual element *OnCreateElement( const string &szType ) const;

  /// Get the scenegraph instance used for parsing
  scenegraph &GetSceneGraph( );

private:
  scenegraph &m_scenegraph;
};
};

#endif
