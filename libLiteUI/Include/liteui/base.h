//
//  liteui::base
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_BASE_H
#define LIBLITEUI_BASE_H

#include <string>

namespace liteui
{
using std::string;

class base
{
public:
  base( const string &szTypeName );
  void SetName( const string &szName );

  const string &GetTypeName( ) const;
  const string &GetName( ) const;
private:
  const string m_szTypeName;
  string m_szName;
};
};

#endif
