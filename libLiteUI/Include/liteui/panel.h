//
//  liteui::panel
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_PANEL_H
#define LIBLITEUI_PANEL_H

#include <liteui/element.h>

namespace liteui
{
class panel
  : public element
{
public:
  panel( );

  virtual void Render( ) { }
  virtual void Update( ) { }
};
};

#endif
