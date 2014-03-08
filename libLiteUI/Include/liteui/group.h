//
//  liteui::group
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_GROUP_H
#define LIBLITEUI_GROUP_H

#include <liteui/element.h>

#include <vector>

namespace liteui
{
using std::vector;
typedef vector<element *>       items;
typedef items::iterator         items_it;
typedef items::const_iterator   items_cit;
class group;
typedef vector<group *>         groups;
typedef groups::iterator        groups_it;
typedef groups::const_iterator  groups_cit;

class group
  : public element
{
public:
  /// Default constructor
  group( );

  /// Virtual destructor
  virtual ~group( );

  /// Add a group object to this scene; the scene will automatically be released when the destructor is called
  void AddGroup( group *pGroup );

  /// Add an element object to this group; the group will automatically be released when the destructor is called
  void AddChild( element *pObj );

  /// Remove an element object to this group
  void RemoveChild( element *pObj );

  /// Check if the element is within the current group
  bool HasChild( element *pObj ) const;

  /// Find child by name
  element *FindChildByName( const string &szName );

  /// Handle a state update; filters through to children if applicable
  virtual void OnMessage( const state_message &msg );

  /// Group-specific rendering
  virtual void Render( ) ;

  /// Group-specific updating
  virtual void Update( ) ;

private:
  /// Vector of child element
  items m_items;
  /// Vector of nested groups
  groups m_groupItems;

  /// Check if this group is already tracked by this scene
  bool HasGroup( group *pGroup ) const;
};
};

#endif
