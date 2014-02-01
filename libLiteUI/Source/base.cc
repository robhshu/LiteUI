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
base::base( const char *cTypeName )
  : m_cTypeName( cTypeName )
  , m_cName( "unnamed" )
{
}

void base::SetName( const char *cName )
{
  if( cName != nullptr ) {
    m_cName = cName;
  }
}

const char *base::GetTypeName( ) const
{
  return m_cTypeName;
}

const char *base::GetName( ) const
{
  return m_cName;
}

};
