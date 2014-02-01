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
  scene( );
  
  void AddGroup( group *pGroup );
  group *FindGroupNyName( const char* cGroupName );

  void RenderScene( );

private:
  groups m_groupItems;

  bool HasGroup( group *pGroup ) const;
};
};

#endif
