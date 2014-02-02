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

class group
  : public element
{
public:
  group( );

  void AddChild( element *pObj );
  void RemoveChild( element *pObj );

  bool HasChild( element *pObj ) const;
  bool HasChildNamed( const char *cName ) const;

  virtual void OnMessage( unsigned px, unsigned py );

  virtual void Render( ) ;
  virtual void Update( ) ;

private:
  items m_items;
};
};

#endif
