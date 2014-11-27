//
//  liteui::group
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_GROUP_H
#define LIBLITEUI_GROUP_H

#include <liteui/common.h>
#include <liteui/element.h>

#include <vector>

namespace liteui
{
using std::vector;
typedef vector<element::ptr>    items;
typedef items::iterator         items_it;
typedef items::const_iterator   items_cit;
class group;
// to avoid dealing with foward declarations of types
typedef vector<std::shared_ptr<group> >      groups;
typedef groups::iterator        groups_it;
typedef groups::const_iterator  groups_cit;

class group
  : public element
{
public:
  REGISTER_CLASS(group);

  /// Default constructor
  group( );

  /// Virtual destructor
  virtual ~group( );

  /// Mark this object as dirty
  virtual void Dirty( bool bAll = false );

  /// Add a group object to this scene; the scene will automatically be released when the destructor is called
  void AddGroup(group::ptr pGroup);

  /// Add an element object to this group; the group will automatically be released when the destructor is called
  void AddChild(element::ptr pObj);

  // uh, can we add a raw child too??

  /// Remove an element object to this group
  void RemoveChildByName(const string &szName);

  /// Check if the element is within the current group
  bool HasChild( element* pObj) const;

  /// Find child by name
  element::ptr FindChildByName(const string &szName);

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

  /// Internal lookup for child
  items_cit FindChildByNameInternal(const string &szName) const;

  /// Check if this group is already tracked by this scene
  bool HasGroup( element* pGroup) const;
};
};

#endif
