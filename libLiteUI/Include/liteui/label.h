//
//  liteui::label
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_LABEL_H
#define LIBLITEUI_LABEL_H

#include <liteui/element.h>
#include <string>

namespace liteui
{
using std::string;

class label
  : public element
{
public:
  label( );
  void SetText( const string &szText );

  const string &GetText( ) const;

  virtual void Render( ) { }
  virtual void Update( ) ;

private:
  string m_szText;
};
};

#endif
