//
//  liteui::panel
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_PANEL_H
#define LIBLITEUI_PANEL_H

#include <liteui/common.h>
#include <liteui/element.h>

namespace liteui
{
class panel
  : public element
{
public:
  REGISTER_CLASS(panel);

  /// Default constructor
  panel( );
  
  /// Virtual destructor
  virtual ~panel( ){ }

  /// Panel-specific rendering; unused
  virtual void Render( ) { }

  /// Panel-specific updating; unused
  virtual void Update( ) { }
};
};

#endif
