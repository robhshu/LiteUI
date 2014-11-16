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
const string base::ms_szDefaultName( "unnamed" );

base::base( const string &szTypeName )
  : m_szTypeName( szTypeName )
  , m_szName( ms_szDefaultName )
  , m_refCount( 0 )
  , m_bDirty( true )
{
}

base::~base( )
{
  assert(m_refCount==0);
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

void base::Dirty( bool bAll /* = false */)
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

const bool base::HasCustomName( ) const
{
  return m_szName != ms_szDefaultName;
}

void base::IncReferenceCount( )
{
  m_refCount++;
}

void base::DecReferenceCount( )
{
  assert(m_refCount > 0);
  m_refCount--;
}

};
