//
//  liteui::scenegraph
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_SCENEGRAPH_H
#define LIBLITEUI_SCENEGRAPH_H

#include <liteui/scene.h>
#include <liteui/group.h>

#include <vector>

namespace liteui
{
using std::vector;
typedef vector<scene* >         scenes;
typedef scenes::iterator        scenes_it;
typedef scenes::const_iterator  scenes_cit;

class scenegraph
{
public:
  /// Default constructor
  scenegraph( );

  /// Fetch the current scene; the scene stack should be handled elsewhere
  scene &GetActiveScene( );

  /// Add a scene to this scenegraph; the scene will automatically be released when the destructor is called
  void AddScene( scene *pScene );
  
private:
  scenes m_sceneList;
};
};

#endif
