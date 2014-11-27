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
  , m_szText( "" )
{
}

label::~label()
{
  m_szText.clear();
}

void label::Release( )
{
 // DecReferenceCount();

  delete this;
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
    element::SetProperty( szProperty, szValue );
  }
}

void label::Update( )
{
  element::Update( );
}

};
