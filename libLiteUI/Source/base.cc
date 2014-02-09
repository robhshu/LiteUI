//
//  liteui::base
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#include <liteui/base.h>
#include <cassert>

namespace liteui
{
base::base( const string &szTypeName )
  : m_szTypeName( szTypeName )
  , m_szName( "unnamed" )
  , m_bDirty( true )
{
}

void base::Release( )
{
  delete this;
}

void base::SetName( const string &szName )
{
  if( m_szName != szName ) {
    m_szName = szName;
  }
}

void base::SetProperty(const string &szProperty, const string &szValue)
{
  if( szProperty == "name" ) {
    SetName( szValue );
  }
}

void base::Dirty( )
{
  m_bDirty = true;
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
