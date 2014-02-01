//
//  liteui::element
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_ELEMENT_H
#define LIBLITEUI_ELEMENT_H

#include <liteui/base.h>
#include <string>

namespace liteui
{
using std::string;

class element
  : public base
{
public:
  element( const string &szTypeName );

  virtual void Render( ) { }

  void SetParent( element *pParent );
  void SetPositionX( unsigned px );
  void SetPositionY( unsigned py );
  void SetPosition( unsigned px, unsigned py );
  void SetWidth( unsigned val );
  void SetHeight( unsigned val );
  void SetUserData( unsigned val );

  unsigned GetWidth( ) const;
  unsigned GetHeight( ) const;

  element *GetParent( ) const;
  unsigned GetRelativeX( ) const;
  unsigned GetRelativeY( ) const;
  unsigned GetAbsoluteX( ) const;
  unsigned GetAbsoluteY( ) const;
  unsigned GetUserData( ) const;

  virtual bool IsPointInside( unsigned px, unsigned py ) const;
  virtual void Update( );

private:
  element *m_pParent;
  unsigned m_posX;
  unsigned m_posY;
  unsigned m_width;
  unsigned m_height;
  unsigned m_userData;

protected:
  bool m_bDirty;
};
};

#endif
