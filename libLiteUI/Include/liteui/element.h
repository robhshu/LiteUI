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

enum element_callback_reason
{
  cb_focus = 0,
  cb_blur,
  cb_press,
  cb_release,

  cb_reason_count
};

class element;

class callback_info
{
private:
  const string m_reason;
  element *m_element;
public:
  /// Default constructor; callback reason and existing object
  callback_info( const string &reason, element *pObj )
    : m_reason( reason )
    , m_element( pObj )
  { }

  /// Get the reason for this callback
  const string &GetReason( ) const
  {
    return m_reason;
  }

  /// Get the object associated with this callback
  element *GetElement( ) const
  {
    return m_element;
  }
};

class element;
typedef void (*element_callback)(const callback_info &info);

class element
  : public base
  , public state
{
public:
  /// Default constructor; a typename is required to create an element
  element( const string &szTypeName );

  /// Virtual destructor
  virtual ~element( );

  /// Destroy this element; todo: virtual
  void Release( );

  /// Virtual rendering function to override
  virtual void Render( ) { }

  /// Set the current parent object of this instance; sets the dirty flag if changed
  void SetParent( element *pParent );

  /// Set the x-position of this instance; sets the dirty flag if changed
  void SetPositionX( unsigned px );

  /// Set the y-position of this instance; sets the dirty flag if changed
  void SetPositionY( unsigned py );

  /// Set the position of this instance; sets the dirty flag if changed
  void SetPosition( unsigned px, unsigned py );

  /// Set the width of this instance; sets the dirty flag if changed
  void SetWidth( unsigned val );

  /// Set the height of this instance; sets the dirty flag if changed
  void SetHeight( unsigned val );

  /// Set custom user-defined data
  void SetUserData( unsigned val );

  /// Get the width of this object
  unsigned GetWidth( ) const;

  /// Get the height of this object
  unsigned GetHeight( ) const;

  /// Get the parent element of this object or nullptr
  element *GetParent( ) const;

  /// Get the x-position of this element relative to the parent
  unsigned GetRelativeX( ) const;

  /// Get the y-position of this element relative to the parent
  unsigned GetRelativeY( ) const;

  /// Get the x-position of this element in the current scene
  unsigned GetAbsoluteX( ) const;

  /// Get the y-position of this element in the current scene
  unsigned GetAbsoluteY( ) const;

  /// Get custom user-defined data value
  unsigned GetUserData( ) const;

  /// Request a member is updated from a property name and property value
  virtual void SetProperty(const string &szProperty, const string &szValue);

  /// Mark this object as dirty; will also set parent as dirty if this object has a parent
  virtual void Dirty( );

  /// Handle a state update
  virtual void OnMessage( const state_message &msg );

  /// Check if a point is within this object instance
  virtual bool IsPointInside( unsigned px, unsigned py ) const;

  /// Element-specific updating
  virtual void Update( );

  /// Virtual function to handle a blur event
  virtual void OnBlur( );

  /// Virtual function to handle a focus event
  virtual void OnFocus( );

  /// Virtual function to handle a select event
  virtual void OnSelect( bool bActive );

  /// Set a state listener callback (optional)
  void SetCallbackFunc( element_callback callback );

  /// Allow the listener callback to handle a specific event
  void SetEventReason( element_callback_reason event, const string &szReason );

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
