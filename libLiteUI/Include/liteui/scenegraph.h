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
#include <vector>

namespace liteui
{
using std::string;
using std::vector;

typedef vector<scene* >             sceneptrvec;
typedef sceneptrvec::iterator       sceneptrvecIt;
typedef sceneptrvec::const_iterator sceneptrvecCIt;

class scenegraph
{
public:
  /// Default constructor
  scenegraph( );

  /// Destructor
  ~scenegraph( );

  /// Create a new scene definition
  scene &CreateScene( );

  /// Adds an untrack scene
  void AddScene( scene &ref );

  /// Destroy scene and remove if owned
  void DestroyScene( scene &ref );

  /// Locate a scene by name
  scene *FindScene( const string &szName );

  /// Release all scenes
  void ClearAll( );
  
private:
  sceneptrvec m_scenes;
};
};

#endif
