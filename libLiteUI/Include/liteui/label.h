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

namespace liteui
{
class label
  : public element
{
public:
  label( );
  void SetText( const char *cText );

  const char *GetText( ) const;

  virtual void Render( ) { }
  virtual void Update( ) { }

private:
  const char *m_cText;
};
};

#endif
