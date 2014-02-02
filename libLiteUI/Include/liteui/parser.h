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

namespace liteui
{
class parser
{
public:
  bool Read( const string &szJson );
  virtual scene *OnCreateScene( ) const;
  virtual element *OnCreateElement( const string &szType ) const;
};
};

#endif
