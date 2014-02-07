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
typedef void (*element_callback)(element*, const string&);

enum element_callback_reason
{
  cb_focus = 0,
  cb_blur,
  cb_press,
  cb_release,

  cb_reason_count
};

class element_message
{
private:
  unsigned m_px;
  unsigned m_py;
  unsigned m_mdown;
public:
  element_message( unsigned px, unsigned py, unsigned mstate )
  {
      Set(px, py, mstate);
  }

  void Set( unsigned px, unsigned py, unsigned mstate )
  {
      m_px    = px;
      m_py    = py;
      m_mdown = mstate;
  }

  unsigned GetCursorX( ) const
  {
    return m_px;
  }

  unsigned GetCursorY( ) const
  {
    return m_py;
  }

  unsigned GetCursorState( ) const
  {
    return m_mdown;
  }
};

class element
  : public base
  , public state
{
public:
  element( const string &szTypeName );

  virtual ~element( );
  void Release( );

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

  virtual void SetProperty(const string &szProperty, unsigned nValue);

  virtual void Dirty( );

  virtual void OnMessage( const element_message &msg );
  virtual bool IsPointInside( unsigned px, unsigned py ) const;
  virtual void Update( );

  virtual void OnBlur( );
  virtual void OnFocus( );
  virtual void OnSelect( bool bActive );

  void SetCallbackFunc( element_callback callback );
  void SetEventReason(element_callback_reason event, const string &szReason);

private:
  element *m_pParent;
  unsigned m_posX;
  unsigned m_posY;
  unsigned m_width;
  unsigned m_height;
  unsigned m_userData;
  element_callback m_eventCallback;
  string m_eventReasons[cb_reason_count];
};
};

#endif
