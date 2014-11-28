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
  REGISTER_CLASS(label);

  /// Default constructor
  label( );

  /// Virtual destructor
  virtual ~label() {}

  /// Set the label text string
  void SetText(const string &szText);

  /// Fetch the label text string
  const string GetText() const;

  /// Label-specific rendering
  virtual void Render( ) { }
  
private:
  string m_szText;
};
};

#endif
