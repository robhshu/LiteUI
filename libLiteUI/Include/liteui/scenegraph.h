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

#include <map>

namespace liteui
{
using std::multimap;
typedef std::pair<unsigned, scene*> sceneMapPair;
typedef multimap<unsigned, scene*>  sceneMap;
typedef sceneMap::iterator          sceneMap_it;
typedef sceneMap::const_iterator    sceneMap_cit;

class scenegraph
{
public:
  /// Default constructor
  scenegraph( );

  /// Destructor
  ~scenegraph( );

  /// Fetch the current scene; the scene stack should be handled elsewhere
  scene &GetActiveScene( );

  /// Go to the next scene
  bool NextScene( );

  /// Go to the previous scene
  bool PreviousScene( );

  /// Add a scene to this scenegraph; the scene will automatically be released when the destructor is called
  void AddScene( scene *pScene, const unsigned uPriority = 0 );

  ///  Get the number of loaded scenes
  unsigned CountScenes( ) const;

  /// Clear everything; active scene reference will be invalid
  void ClearAll( );
  
private:
  sceneMap m_sceneList;
  sceneMap_it m_active;
};
};

#endif
