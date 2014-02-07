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

label::~label()
{
  m_szText.clear();
}

void label::SetText( const string &szText )
{
  if( m_szText != szText ) {
    m_szText = szText;
    Dirty();
  }
}

const string &label::GetText( ) const
{
  return m_szText;
}

void label::SetProperty(const string &szProperty, const string &szValue)
{
  if( szProperty == "text" ) {
    SetText( szValue );
  } else {
    base::SetProperty( szProperty, szValue );
  }
}

void label::Update( )
{
  element::Update( );
}

unsigned label::GetTextLength( ) const
{
  return m_szText.length();
}

};
