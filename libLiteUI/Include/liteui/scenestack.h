//
//  liteui::scenestack
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Mar 2014
//
#ifndef LIBLITEUI_SCENESTACK_H
#define LIBLITEUI_SCENESTACK_H

#include <liteui/common.h>
#include <liteui/scene.h>
#include <liteui/scenegraph.h>

#include <vector>

namespace liteui
{
using std::vector;

typedef vector<scene* >             sceneptrvec;
typedef sceneptrvec::iterator       sceneptrvecIt;
typedef sceneptrvec::const_iterator sceneptrvecCIt;

class scenestack
{
public:
  /// Default constructor
  scenestack( scenegraph &sg );

  /// Destructor
  ~scenestack( );

  /// Add scene
  void PushScene( const string &szName, bool bAllowDuplicate = false );

  /// Remove top scene
  void PopScene( );

  /// Remove all scenes
  void Clear( );

  /// Render all scenes on the stack
  void Render( );

  /// Update all scenes in the stack, messaging the top
  void UpdateAll( );

  /// Get the foremost scene
  scene &Top( ) const;

  /// Check if the foremost scene is top by name
  bool IsTop( const string &szName ) const;

  /// Check if the stack is empty or not
  bool Empty( ) const;
private:
  scenegraph &m_sceneGraph;

  sceneptrvec m_sceneStack;

  /// Find scene by name
  bool HasScene( const string &szName ) const;

  scenestack(const scenestack&);
  scenestack& operator=(const scenestack&);
};
};

#endif
