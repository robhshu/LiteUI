//
//  liteui::state
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_STATE_H
#define LIBLITEUI_STATE_H

#include <liteui/common.h>

namespace liteui
{
class state_message
{
private:
  n_unit m_px;
  n_unit m_py;
  unsigned m_state;
public:
  /// Construct using a focus position and a pressed state flag
  state_message( n_unit uPosX, n_unit uPosY, bool bPointerDown)
    : m_px( 0 )
    , m_py( 0 )
    , m_state( 0 )
  {
      Set(uPosX, uPosY, bPointerDown);
  }

  /// Update the focus position and pressed state flag
  void Set( n_unit uPosX, n_unit uPosY, bool bPointerDown )
  {
      m_px        = uPosX;
      m_py        = uPosY;
      if( !bPointerDown ) {
        m_state   = 0;        // up
      } else {
        if( m_state != 0 ) {
          m_state = 2;        // held
        } else {
          m_state = 1;        // pressed
        }
      }
  }

  /// Fetch the cursor x-position
  n_unit GetCursorX( ) const
  {
    return m_px;
  }

  /// Fetch the cursor y-position
  n_unit GetCursorY( ) const
  {
    return m_py;
  }

  /// Fetch the raw cursor state
  unsigned GetCursorState( ) const
  {
    return m_state;
  }

  /// Fetch the flag which determines if a pointer has just been pressed or not
  bool HasPointerPress( ) const
  {
    return m_state == 1;
  }
  
  /// Fetch the flag which determines if a pointer is held down or not
  bool HasPointerHeld( ) const
  {
    return m_state >= 1;
  }
};

class state
{
private:
  class state_internal
  {
  public:
    bool m_highlighted;
    bool m_selected;
    bool m_held;

    /// Constructor
    state_internal();
  };

  state_internal m_internalState;
public:
  /// Virtual function to handle a focus event
  virtual void OnFocus( ) { }

  /// Virtual function to handle a blur event
  virtual void OnBlur( ) { }

  /// Virtual function to handle a select event
  virtual void OnSelect(bool UNUSED(bActive) ) { }

  /// Flag to determine if there is focus
  bool IsHighlighted( ) const;

  /// Flag to determine if there is selection
  bool IsSelected( ) const;

  /// Update the raw state flags
  void UpdateStateRaw( bool bHighlighted, bool bSelected );

protected:
  /// Constructor; this object can only be inherited
  state( );

  /// Update the state flags; safter than UpdateStateRaw
  void UpdateState( bool bHighlighted, bool bSelected );
};

};

#endif
