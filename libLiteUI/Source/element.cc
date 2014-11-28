//
//  liteui::element
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#include <liteui/element.h>

namespace liteui
{
element::element( const string &szTypeName )
  : base( szTypeName )
  , m_pParent( nullptr )
  , m_userData(0)
  , m_posX( 0 )
  , m_posY( 0 )
  , m_width( 1 )
  , m_height( 1 )
  , m_bVisible( true )
  , m_anchor_tl( 0 )
  , m_anchor_tr( 0 )
  , m_anchor_bl( 0 )
  , m_anchor_br( 0 )
  , m_eventCallback( nullptr )
  , m_eventCallbackData( nullptr )
{
}

element::~element( )
{
  m_pParent = nullptr;
}

void element::SetParent( element *pParent )
{
  if (m_pParent != pParent) {
    m_pParent = pParent;
    MarkDirty();
  }
}

void element::SetVisible( bool bFlag )
{
  if( m_bVisible != bFlag ) {
    m_bVisible = bFlag;
    MarkDirty();
  }
}

void element::SetPositionX( n_unit px )
{
  if( m_posX != px ) {
    m_posX = px;
    MarkDirty();
  }
}

void element::SetPositionY( n_unit py )
{
  if( m_posY != py ) {
    m_posY = py;
    MarkDirty();
  }
}

void element::SetPosition( n_unit px, n_unit py )
{
  SetPositionX( px );
  SetPositionY( py );
}

void element::SetWidth( n_unit val )
{
  if( val >= n_unit(0) ) {
    m_width = val;
    MarkDirty();
  }
}

void element::SetHeight( n_unit val ) {
  if( val >= n_unit(0) ) {
    m_height = val;
    MarkDirty();
  }
}

void element::SetUserData( unsigned val )
{
  m_userData = val;
}

void element::SetAnchorFlags( bool tl, bool tr, bool bl, bool br )
{
  m_anchor_tl = ( tl ? 1 : 0 );
  m_anchor_tr = ( tr ? 1 : 0 );
  m_anchor_bl = ( bl ? 1 : 0 );
  m_anchor_br = ( br ? 1 : 0 );
}

element *element::GetParent( ) const
{
  return m_pParent;
}

bool element::IsVisible( ) const
{
  return m_bVisible && m_width > 0.0 && m_height > 0.0;
}

n_unit element::GetRelativeX( ) const
{
  return m_posX;
}

n_unit element::GetRelativeY( ) const
{
  return m_posY;
}

n_unit element::GetAbsoluteX( ) const
{
  const n_unit my_x = GetRelativeX( );

  if( GetParent() ) {
    return GetParent()->GetAbsoluteX() + my_x;
  } else {
    return my_x;
  }
}

n_unit element::GetAbsoluteY( ) const
{
  const n_unit my_y = GetRelativeY( );

  if( GetParent() ) {
    return GetParent()->GetAbsoluteY() + my_y;
  } else {
    return my_y;
  }
}

unsigned element::GetUserData( ) const
{
  return m_userData;
}

/// Get the width of this object from a scene
unit element::GetWidthInScene(n_unit scale_x) const
{
  return static_cast<unit>(m_width * scale_x);
}

/// Get the height of this object from a scene
unit element::GetHeightInScene(n_unit scale_y) const
{
  return static_cast<unit>(m_height * scale_y);
}

n_unit element::GetWidth( ) const
{
  return m_width;
}

n_unit element::GetHeight( ) const
{
  return m_height;
}

bool element::GetAnchorFlags( bool &tl, bool &tr, bool &bl, bool &br ) const
{
  tl = ( m_anchor_tl != 0 );
  tr = ( m_anchor_tr != 0 );
  bl = ( m_anchor_bl != 0 );
  br = ( m_anchor_br != 0 );
  
  return tl || tr || bl || br;
}

void element::MarkDirty()
{
  base::MarkDirty();

  if( GetParent() ) {
    GetParent()->MarkDirty();
  }
}

void element::OnMessage( const state_message &msg )
{
  if( !IsVisible() ) {
    return;
  }

  const bool bPointInside = IsPointInside( msg.GetCursorX(), msg.GetCursorY() );
  
  const bool hover_change = ( IsHighlighted() != bPointInside );
  const bool select_change = ( IsSelected() != msg.HasPointerHeld() );

  if( hover_change ) {

    // any hover change will stop it being selected
    UpdateState( bPointInside, false );

  } else if (IsHighlighted() && select_change) {

    // we only care if this is within the element
    if( bPointInside ) {
      if( msg.HasPointerPress() ) {
        // update local selected flag when pressed the first time

        UpdateState( true, true );
      } else if( !msg.HasPointerHeld() ) {
        // remove the local selected flag when released

        UpdateState( true, false );
      }
    }
  }
}

bool element::IsPointInside( n_unit px, n_unit py ) const
{
  if( !IsVisible() ) {
    return false;
  }

  px -= GetAbsoluteX();
  py -= GetAbsoluteY();

  return( px >= 0 && px <= GetWidth()
    && py >= 0 && py <= GetHeight() );
}

void element::UpdateAttributes()
{
  string szValue;

  // Properties

  if (GetAttribute("visible", szValue)) {
    const bool is_visible(szValue.c_str()[0] != '0');
    SetVisible(is_visible);
  }

  if (GetAttribute("width", szValue)) {
    const n_unit val(TO_N_UNIT(szValue.c_str()));
    SetWidth(val);
  }

  if (GetAttribute("height", szValue)) {
    const n_unit val(TO_N_UNIT(szValue.c_str()));
    SetHeight(val);
  }

  if (GetAttribute("pos_x", szValue)) {
    const n_unit val(TO_N_UNIT(szValue.c_str()));
    SetPositionX(val);
  }

  if (GetAttribute("pos_y", szValue)) {
    const n_unit val(TO_N_UNIT(szValue.c_str()));
    SetPositionY(val);
  }

  if (GetAttribute("anchor", szValue)) {
    bool tl = (strstr(szValue.c_str(), "tl") != nullptr);
    bool tr = (strstr(szValue.c_str(), "tr") != nullptr);
    bool bl = (strstr(szValue.c_str(), "bl") != nullptr);
    bool br = (strstr(szValue.c_str(), "br") != nullptr);

    SetAnchorFlags(tl, tr, bl, br);
  }

  // Events

  SetEventReason(element_callback_reason::cb_focus, GetAttribute("onFocus"));
  SetEventReason(element_callback_reason::cb_blur, GetAttribute("onBlur"));
  SetEventReason(element_callback_reason::cb_press, GetAttribute("onPress"));
  SetEventReason(element_callback_reason::cb_release, GetAttribute("onRelease"));
}

void element::Update( )
{
  m_bDirty = false;

  if( !IsVisible() ) {
    return;
  }

  UpdateAttributes();

  if( GetParent() ) {
    // expand horizontally
    if( ( m_anchor_tl && m_anchor_tr ) || ( m_anchor_bl && m_anchor_br ) ) {
      SetWidth( GetParent()->GetWidth() );
    }

    // expand vertically
    if( ( m_anchor_tl && m_anchor_bl ) || ( m_anchor_tr && m_anchor_br ) ) {
      SetHeight( GetParent()->GetHeight() );
    }

    if( m_anchor_tl ) {
      SetPositionX( 0 );
      SetPositionY( 0 );
    } else if( m_anchor_tr ) {
      SetPositionX( GetParent()->GetWidth() - GetWidth() );
      SetPositionY( 0 );
    }

    if( m_anchor_bl ) {
      SetPositionX(0);
      SetPositionY( GetParent()->GetHeight() - GetHeight() );
    } else if( m_anchor_br ) {
      SetPositionX( GetParent()->GetWidth() - GetWidth() );
      SetPositionY( GetParent()->GetHeight() - GetHeight() );
    }
  }
}

void element::SetCallbackFunc( element_callback callback )
{
  SetCallbackFunc( callback, nullptr );
}

void element::SetCallbackFunc( element_callback callback, void *userdata )
{
  m_eventCallback = callback;
  m_eventCallbackData = userdata;
}

void element::SetEventReason(element_callback_reason event, const string &szReason)
{
  if( event < cb_reason_count ) {
    m_eventReasons[event] = szReason;
  }
}

void element::OnBlur( )
{
  if( !IsVisible() ) {
    return;
  }

  if( !m_eventReasons[cb_blur].empty() && m_eventCallback != nullptr ) {
    callback_info cb_info( m_eventReasons[cb_blur], this, m_eventCallbackData );
    (*m_eventCallback)(cb_info);
  }
}

void element::OnFocus( )
{
  if( !IsVisible() ) {
    return;
  }

  if( !m_eventReasons[cb_focus].empty() && m_eventCallback != nullptr ) {
    callback_info cb_info( m_eventReasons[cb_focus], this, m_eventCallbackData );
    (*m_eventCallback)(cb_info);
  }
}

void element::OnSelect( bool bActive )
{
  if( !IsVisible() ) {
    return;
  }

  if( m_eventCallback != nullptr ) {
    if( bActive ) {
      if( !m_eventReasons[cb_press].empty() ) {
        callback_info cb_info( m_eventReasons[cb_press], this, m_eventCallbackData );
        (*m_eventCallback)(cb_info);
      }
    } else {
      if( !m_eventReasons[cb_release].empty() ) {
        callback_info cb_info( m_eventReasons[cb_release], this, m_eventCallbackData );
        (*m_eventCallback)(cb_info);
      }
    }
  }
}

};
