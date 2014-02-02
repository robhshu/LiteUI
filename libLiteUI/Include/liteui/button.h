//
//  liteui::button
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_BUTTON_H
#define LIBLITEUI_BUTTON_H

#include <liteui/element.h>

namespace liteui
{
class button
  : public element
{
public:
  button( );
  virtual ~button( ) { }

  virtual void Render( ) { }
  virtual void Update( ) ;
};
};

#endif
