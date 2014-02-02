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
{
}

state::state( )
{
}

void state::UpdateState( bool bHighlighted )
{
  if( bHighlighted != m_internalState.m_highlighted ) {
    if( bHighlighted && !m_internalState.m_highlighted ) {
      OnFocus( );
    } else {
      OnBlur( );
    }

    m_internalState.m_highlighted = bHighlighted;
  }
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
