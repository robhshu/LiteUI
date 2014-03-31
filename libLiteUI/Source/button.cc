//
//  liteui::button
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#include <liteui/button.h>

namespace liteui
{

button::button( )
  : element( "button" )
{
}

button::~button( )
{

}

void button::Release( )
{
  DecReferenceCount();

  delete this;
}

void button::Update( )
{
  element::Update( );
}

};
