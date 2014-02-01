//
//  liteui::label
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#include <liteui/label.h>

namespace liteui
{

label::label( )
  : element( "label" )
  , m_szText( "LabelText" )
{
}

void label::SetText( const string &szText )
{
  if( m_szText.compare( szText ) != 0 ) {
    m_szText = szText;
    m_bDirty = true;
  }
}

const string &label::GetText( ) const
{
  return m_szText;
}

void label::Update( )
{
  element::Update( );
}

};
