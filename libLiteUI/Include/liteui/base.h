//
//  liteui::base
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_BASE_H
#define LIBLITEUI_BASE_H

#include <liteui/common.h>

#include <string>
#include <map>
#include <memory>

namespace liteui
{
using std::string;
using std::map;
using std::unique_ptr;
using std::shared_ptr;

#define REGISTER_CLASS(name) \
  public: \
    typedef name* inst; \
    typedef shared_ptr<name> ptr; \
    typedef unique_ptr<name> uptr;

class base
{
public:
  typedef map<string, string> attributes;

  /// Construct using a typename string to aid with debugging this object
  base( const string &szTypeName );

  /// Virtual destructor
  virtual ~base( );

  /// Update the name of this object (optional)
  void SetName( const string &szName );
  
  /// Set the value of an attribute
  void SetAttribute(const string &szAttribName, const string &szValue);

  /// Set the value of an attribute, marking the instance dirty
  void SetAttributeDirty(const string &szAttribName, const string &szValue);

  /// Fetch the value of a specific attribute
  const string GetAttribute(const string &szAttribName) const;

  /// Alternate function to fetch the value of a specific attribute
  bool GetAttribute(const string &szAttribName, string& value) const;

  /// Check a property has been set
  bool HasAttribute(const string &szAttribName) const;
  
  /// Mark this object as dirty
  virtual void Dirty( bool bAll = false );

  /// Get the typename of this object
  const string &GetTypeName( ) const;
  
  /// Get the name of this object
  const string GetName( ) const;

  /// Is this object named
  const bool HasCustomName( ) const;

private:
  static const string ms_szDefaultName;
  const string m_szTypeName;
  attributes m_attributes;

  base(const base&){ }
  base& operator=(const base&) {}

protected:
  /// Flag to mark this object for update
  bool m_bDirty;
};
};

#endif
