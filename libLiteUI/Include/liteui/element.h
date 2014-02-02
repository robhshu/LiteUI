//
//  liteui::element
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_ELEMENT_H
#define LIBLITEUI_ELEMENT_H

#include <liteui/base.h>
#include <liteui/state.h>
#include <string>

namespace liteui
{
using std::string;

class element;
typedef void (*element_callback)(element*);

enum element_callback_reason
{
  cb_focus = 0,
  cb_blur,

  cb_reason_count
};

class element
  : public base
  , public state
{
public:
  element( const string &szTypeName );

  virtual void Render( ) { }

  void SetParent( element *pParent );
  void SetPositionX( unsigned px );
  void SetPositionY( unsigned py );
  void SetPosition( unsigned px, unsigned py );
  void SetWidth( unsigned val );
  void SetHeight( unsigned val );
  void SetUserData( unsigned val );

  unsigned GetWidth( ) const;
  unsigned GetHeight( ) const;

  element *GetParent( ) const;
  unsigned GetRelativeX( ) const;
  unsigned GetRelativeY( ) const;
  unsigned GetAbsoluteX( ) const;
  unsigned GetAbsoluteY( ) const;
  unsigned GetUserData( ) const;

  virtual void OnMessage( unsigned px, unsigned py );
  virtual bool IsPointInside( unsigned px, unsigned py ) const;
  virtual void Update( );

  virtual void OnBlur( );
  virtual void OnFocus( );

  void SetCallback( element_callback_reason method, element_callback callback );

private:
  element *m_pParent;
  unsigned m_posX;
  unsigned m_posY;
  unsigned m_width;
  unsigned m_height;
  unsigned m_userData;
  element_callback m_callbacks[cb_reason_count];

protected:
  bool m_bDirty;
};
};

#endif
