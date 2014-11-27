//
//  liteui::scene
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_SCENE_H
#define LIBLITEUI_SCENE_H

#include <liteui/common.h>
#include <liteui/base.h>
#include <liteui/group.h>

#include <vector>

namespace liteui
{
using std::vector;

class scene
  : public base
{
public:
  REGISTER_CLASS(scene);

  /// Default constructor
  scene( );

  /// Virtual destructor
  virtual ~scene( );

  /// Release this object
  void Release( );
  
  /// Mark this object as dirty
  virtual void Dirty( bool bAll = false );

  /// Add a group object to this scene; the scene will automatically be released when the destructor is called
  void AddGroup( group::ptr pGroup);

  /// Update the cursor position and mouse state within this scene
  void SetCursor( n_unit px, n_unit py, bool bPressed );

  /// Update all elements within this scene
  void UpdateScene( bool bMessage );

  /// Render elements within this scene
  void RenderScene( );

  /// Update the bounds of this scene
  void SetVirtualDimensions(n_unit width, n_unit height);

  /// Get object user data
  bool GetObjectUserData( const string &szName, unsigned &user_data );

  /// Set object user data
  bool SetObjectUserData( const string &szName, const unsigned user_data );
private:
  groups m_groupItems;
  state_message m_lastMsg;

  /// Size of the scene
  n_unit bound_w, bound_h;

  /// Check if this group is already tracked by this scene
  bool HasGroup(group *pGroup); //const;

  /// Find child by name
  element *FindChildByName( const string &szName );
};
};

#endif
