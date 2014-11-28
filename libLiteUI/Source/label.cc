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
{
}

void label::SetText(const string &szText)
{
  if (GetText() != szText) {
    SetAttributeDirty("text", szText);
  }
}

const string label::GetText() const
{
  return GetAttribute("text");
}

};
