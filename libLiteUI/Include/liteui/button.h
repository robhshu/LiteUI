//
//  liteui::button
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_BUTTON_H
#define LIBLITEUI_BUTTON_H

#include <liteui/common.h>
#include <liteui/element.h>

namespace liteui
{
class button
  : public element
{
public:
  REGISTER_CLASS(button);

  /// Default constructor
  button( );
  
  /// Virtual destructor
  virtual ~button( );

  /// Release this object
  virtual void Release( );

  /// Button-specific rendering; unused
  virtual void Render( ) { }

  /// Button-specific updating
  virtual void Update( ) ;
};
};

#endif
