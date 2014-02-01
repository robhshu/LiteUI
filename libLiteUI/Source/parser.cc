//
//  liteui::parser
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#include <liteui/parser.h>

namespace liteui
{

bool parser::LoadRaw( const char *sceneDesc, scenegraph& ref )
{
  if( !sceneDesc ) {
    return false;
  }

  //jsmn_parser json_parser;
  //jsmn_init( &json_parser );

  //const unsigned max_tokens = 100;

  //jsmntok_t tokens[max_tokens];
  //memset( tokens, 0, sizeof(tokens) * max_tokens );

  //const jsmnerr_t result = jsmn_parse(&json_parser, sceneDesc, tokens, 10);
  //if( result != JSMN_SUCCESS ) {
  //    // error occured
  //    return false;
  //}
  
  // todo: merge with ref

  return true;
}

};
