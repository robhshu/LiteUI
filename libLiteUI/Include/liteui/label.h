//
//  liteui::label
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#ifndef LIBLITEUI_LABEL_H
#define LIBLITEUI_LABEL_H

#include <liteui/common.h>
#include <liteui/element.h>
#include <string>

namespace liteui
{
using std::string;

class label
  : public element
{
public:
  /// Default constructor
  label( );

  /// Virtual destructor
  virtual ~label();

  /// Release this object
  virtual void Release( );

  /// Set the text label property of this object
  void SetText( const string &szText );

  /// Get the text label property of this object
  const string &GetText( ) const;

  /// Request a label-specific member is updated from a property name and property value
  virtual void SetProperty(const string &szProperty, const string &szValue);

  /// Label-specific rendering
  virtual void Render( ) { }

  /// Label-specific updating
  virtual void Update( ) ;

private:
  string m_szText;
};
};

#endif
