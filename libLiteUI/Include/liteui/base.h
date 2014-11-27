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
#include <memory>

namespace liteui
{
using std::string;
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
  /// Construct using a typename string to aid with debugging this object
  base( const string &szTypeName );

  /// Virtual destructor
  virtual ~base( );

  /// Update the name of this object (optional)
  void SetName( const string &szName );
  
  /// Request a member is updated from a property name and property value
  virtual void SetProperty(const string &szProperty, const string &szValue);
  
  /// Mark this object as dirty
  virtual void Dirty( bool bAll = false );

  /// Get the typename of this object
  const string &GetTypeName( ) const;
  
  /// Get the name of this object
  const string &GetName( ) const;

  /// Is this object named
  const bool HasCustomName( ) const;

private:
  static const string ms_szDefaultName;
  const string m_szTypeName;
  string m_szName;
protected:
  /// Flag to mark this object for update
  bool m_bDirty;
};
};

#endif
