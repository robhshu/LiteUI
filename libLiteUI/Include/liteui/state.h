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
class state
{
private:
  class state_internal
  {
  public:
    bool m_highlighted : 1;
    bool m_selected : 1;

    state_internal();
  };

  state_internal m_internalState;

public:
  virtual void OnFocus( ) { }
  virtual void OnBlur( ) { }

  bool IsHighlighted( ) const;
  bool IsSelected( ) const;

  void UpdateStateRaw( bool bHighlighted );

protected:
  state( );

  void UpdateState( bool bHighlighted );
};

};

#endif
