//
//  liteui::state
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#include <liteui/state.h>

namespace liteui
{
state::state_internal::state_internal( )
  : m_highlighted( false )
  , m_selected( false )
  , m_held( false )
{
}

state::state( )
{
}

void state::UpdateState( bool bHighlighted, bool bSelected )
{
  // multiple events can be fired off here
  
  if( bHighlighted != m_internalState.m_highlighted ) {
    if( bHighlighted && !m_internalState.m_highlighted ) {
      OnFocus( );
    } else {
      OnBlur( );
      bSelected = false;
    }

    m_internalState.m_highlighted = bHighlighted;
  }

  if( ( bSelected != m_internalState.m_selected ) ) {
    if( bSelected && !m_internalState.m_selected ) {
      OnSelect(true);
    } else {
      OnSelect(false);
    }

    m_internalState.m_selected = bSelected;
  }
}

void state::UpdateStateRaw( bool bHighlighted, bool bSelected )
{
  UpdateState( bHighlighted, bSelected );
}

bool state::IsHighlighted( ) const
{
  return m_internalState.m_highlighted;
}

bool state::IsSelected( ) const
{
  return m_internalState.m_selected;
}

};
