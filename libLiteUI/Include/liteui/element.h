//
//  liteui::element
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_ELEMENT_H
#define LIBLITEUI_ELEMENT_H

#include <liteui/common.h>
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
  void *m_userdata;
public:
  /// Default constructor; callback reason and existing object
  callback_info( const string &reason, element *pObj )
    : m_reason( reason )
    , m_element( pObj )
    , m_userdata( nullptr )
  { }

  /// Default constructor; callback reason, existing object, and userdata
  callback_info( const string &reason, element *pObj, void *userdata )
    : m_reason( reason )
    , m_element( pObj )
    , m_userdata( userdata )
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

  /// Get the user data (may be null)
  void *GetUserdata( ) const
  {
    return m_userdata;
  }
};

#include <memory>

class element;
typedef void (*element_callback)(const callback_info &info);

class element
  : public base
  , public state
{
public:
  REGISTER_CLASS(element);

  /// Default constructor; a typename is required to create an element
  element( const string &szTypeName );

  /// Virtual destructor
  virtual ~element( );

  /// Virtual rendering function to override
  virtual void Render( ) { }

  /// Set the current parent object of this instance; sets the dirty flag if changed
  void SetParent( element* pParent);

  /// Set the visibility of this item
  void SetVisible( bool bFlag );

  /// Set the x-position of this instance; sets the dirty flag if changed
  void SetPositionX( n_unit px_n );

  /// Set the y-position of this instance; sets the dirty flag if changed
  void SetPositionY( n_unit py_n );

  /// Set the position of this instance; sets the dirty flag if changed
  void SetPosition( n_unit px_n, n_unit py_n );

  /// Set the width of this instance; sets the dirty flag if changed
  void SetWidth( n_unit val_n );

  /// Set the height of this instance; sets the dirty flag if changed
  void SetHeight( n_unit val_n );

  /// Set custom user-defined data
  void SetUserData( unsigned val );

  /// Set the anchor flags
  void SetAnchorFlags( bool tl, bool tr, bool bl, bool br );

  /// Get the width of this object from a scene
  unit GetWidthInScene(n_unit scale_x) const;

  /// Get the height of this object from a scene
  unit GetHeightInScene(n_unit scale_y) const;

  /// Get the width of this object
  n_unit GetWidth( ) const;

  /// Get the height of this object
  n_unit GetHeight( ) const;

  /// Get the parent element of this object or nullptr
  element* GetParent( ) const;

  /// Get the visibility of this element
  bool IsVisible( ) const;

  /// Get the x-position of this element relative to the parent
  n_unit GetRelativeX( ) const;

  /// Get the y-position of this element relative to the parent
  n_unit GetRelativeY( ) const;

  /// Get the x-position of this element in the current scene
  n_unit GetAbsoluteX( ) const;

  /// Get the y-position of this element in the current scene
  n_unit GetAbsoluteY( ) const;

  /// Get custom user-defined data value
  unsigned GetUserData( ) const;

  /// Fetch the anchor flags
  bool GetAnchorFlags( bool &tl, bool &tr, bool &bl, bool &br ) const;

  /// Mark this object as dirty; will also set parent as dirty if this object has a parent
  virtual void Dirty( );

  /// Handle a state update
  virtual void OnMessage( const state_message &msg );

  /// Check if a point is within this object instance
  virtual bool IsPointInside( n_unit px, n_unit py ) const;

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

  /// Set a state listener callback with user data (optional)
  void SetCallbackFunc( element_callback callback, void *userdata );

  /// Allow the listener callback to handle a specific event
  void SetEventReason( element_callback_reason event, const string &szReason );

  void StartDrag( unsigned px, unsigned py );
  void StopDrag( );

private:
  element *m_pParent;
  n_unit m_posX;
  n_unit m_posY;
  n_unit m_width;
  n_unit m_height;
  unsigned m_userData;
  bool m_bVisible;
  bool m_bDragging;
  unsigned m_dragX;
  unsigned m_dragY;
  unsigned
    m_anchor_tl : 1,
    m_anchor_tr : 1,
    m_anchor_bl : 1,
    m_anchor_br : 1;
  element_callback m_eventCallback;
  void *m_eventCallbackData;
  string m_eventReasons[cb_reason_count];

  void UpdateAttributes();
};
};

#endif
