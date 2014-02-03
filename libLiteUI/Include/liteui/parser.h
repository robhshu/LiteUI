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
  parser( scenegraph &sgRef );

  bool Read( const string &szXML );

  virtual scene *OnCreateScene( ) const;
  virtual element *OnCreateElement( const string &szType ) const;

  scenegraph &GetSceneGraph( );

private:
  scenegraph &m_scenegraph;
};
};

#endif
