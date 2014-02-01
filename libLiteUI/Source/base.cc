//
//  liteui::base
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#include <liteui/base.h>

namespace liteui
{
base::base( const string &szTypeName )
  : m_szTypeName( szTypeName )
  , m_szName( "unnamed" )
{
}

void base::SetName( const string &szName )
{
  if( m_szName.compare( szName ) != 0 ) {
    m_szName = szName;
  }
}

const string &base::GetTypeName( ) const
{
  return m_szTypeName;
}

const string &base::GetName( ) const
{
  return m_szName;
}

};
