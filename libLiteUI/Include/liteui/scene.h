//
//  liteui::scene
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_SCENE_H
#define LIBLITEUI_SCENE_H

#include <liteui/base.h>
#include <liteui/group.h>

#include <vector>

namespace liteui
{
using std::vector;
typedef vector<group *>         groups;
typedef groups::iterator        groups_it;
typedef groups::const_iterator  groups_cit;

class scene
  : public base
{
public:
  /// Default constructor
  scene( );
  
  /// Add a group object to this scene; the scene will automatically be released when the destructor is called
  void AddGroup( group *pGroup );

  /// Check if the group is within the current scene
  group *FindGroupNyName( const char* cGroupName );

  /// Update the cursor position and mouse state within this scene
  void SetCursor( unsigned px, unsigned py, bool bPressed );

  /// Render elements within this scene
  void RenderScene( );
private:
  groups m_groupItems;
  state_message m_lastMsg;

  /// Update all elements within this scene
  void UpdateScene( );

  /// Check if this group is already tracked by this scene
  bool HasGroup( group *pGroup ) const;
};
};

#endif
