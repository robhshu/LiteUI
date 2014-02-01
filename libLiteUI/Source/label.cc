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
  , m_cText( "LabelText" )
{
  Update();
}

void label::SetText( const char *cText )
{
  if( cText != nullptr ) {
    m_cText = cText;
    Update();
  }
}

const char *label::GetText( ) const
{
  return m_cText;
}

};
