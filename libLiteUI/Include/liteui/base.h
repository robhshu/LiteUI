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
  /// Construct using a typename string to aid with debugging this object
  base( const string &szTypeName );

  /// Update the name of this object (optional)
  void SetName( const string &szName );
  
  /// Request a member is updated from a property name and property value
  virtual void SetProperty(const string &szProperty, const string &szValue);
  
  /// Mark this object as dirty
  virtual void Dirty( );

  /// Get the typename of this object
  const string &GetTypeName( ) const;
  
  /// Get the name of this object
  const string &GetName( ) const;
private:
  const string m_szTypeName;
  string m_szName;
protected:
  /// Flag to mark this object for update
  bool m_bDirty;
};
};

#endif
