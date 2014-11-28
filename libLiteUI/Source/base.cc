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
  , m_bDirty( true )
{
  SetName(ms_szDefaultName);
}

base::~base( )
{
}

void base::SetName( const string &szName )
{
  SetAttribute("name", szName);
}

void base::SetAttribute(const string &szAttribName, const string &szValue)
{
  if (!szAttribName.empty()) {
    m_attributes[szAttribName] = szValue;
  }
}

void base::SetAttributeDirty(const string &szAttribName, const string &szValue)
{
  if (!szAttribName.empty()) {
    m_attributes[szAttribName] = szValue;
    Dirty();
  }
}

const string base::GetAttribute(const string &szAttribName) const
{
  if (!szAttribName.empty()) {
    attributes::const_iterator res(m_attributes.find(szAttribName));
    if (res != m_attributes.end()) {
      return res->second;
    }
  }

  return "";
}

bool base::GetAttribute(const string &szAttribName, string& value) const
{
  if (!szAttribName.empty()) {
    attributes::const_iterator res(m_attributes.find(szAttribName));
    if (res != m_attributes.end()) {
      value = res->second;
      return true;
    }
  }

  return false;
}

bool base::HasAttribute(const string &szAttribName) const
{
  return m_attributes.find(szAttribName) != m_attributes.end();
}

void base::Dirty( bool /* bAll = false */)
{
  m_bDirty = true;
}

const string &base::GetTypeName( ) const
{
  return m_szTypeName;
}

const string base::GetName( ) const
{
  return GetAttribute("name");
}

const bool base::HasCustomName( ) const
{
  return GetName() != ms_szDefaultName;
}

};
