//
//  liteui::base
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_BASE_H
#define LIBLITEUI_BASE_H

namespace liteui
{
class base
{
public:
  base( const char *cTypeName );
  void SetName( const char *cName );

  const char *GetTypeName( ) const;
  const char *GetName( ) const;
private:
  const char *m_cTypeName;
  const char *m_cName;
};
};

#endif
