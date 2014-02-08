//
//  liteui::state
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_STATE_H
#define LIBLITEUI_STATE_H

namespace liteui
{
class state_message
{
private:
  unsigned m_px;
  unsigned m_py;
  unsigned m_mdown;
public:
  /// Construct using a focus position and the a state flag
  state_message( unsigned px, unsigned py, unsigned mstate )
  {
      Set(px, py, mstate);
  }

  /// Update the focus position and state flag
  void Set( unsigned px, unsigned py, unsigned mstate )
  {
      m_px    = px;
      m_py    = py;
      m_mdown = mstate;
  }

  /// Fetch the cursor x-position
  unsigned GetCursorX( ) const
  {
    return m_px;
  }

  /// Fetch the cursor y-position
  unsigned GetCursorY( ) const
  {
    return m_py;
  }

  /// Fetch the cursor state
  unsigned GetCursorState( ) const
  {
    return m_mdown;
  }
};

class state
{
private:
  class state_internal
  {
  public:
    bool m_highlighted : 1;
    bool m_selected : 1;

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
  virtual void OnSelect( bool bActive ) { }

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
