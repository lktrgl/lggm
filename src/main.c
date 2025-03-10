/* to enable tracing UNcomment the following line */
/*
#define DBGPRN_HEADER_BASED_ENABLED
#define DBGPRN_ENABLED
#define DBGPRN_TO_STDOUT
*/
#include "lggm/dbgprn.h"

/*---------------------------------------------------------------------------*/

#include <stdint.h>
#include <assert.h>
#include <string.h>

/*---------------------------------------------------------------------------*/

void doCLggmTest()
{
  LGGM_CALL_IN();

  LGGM_PRINT_MSG ( "before trace" );
  LGGM_TRACE();

#ifdef DBGPRN_ENABLED
  int a = 7;
#endif /* DBGPRN_ENABLED */

  LGGM_PRINT_INT ( a );

#ifdef DBGPRN_ENABLED
  const char* s = "a string";
#endif /* DBGPRN_ENABLED */

  LGGM_PRINT_STR_N ( s, 5 );

  LGGM_PRINT_STR ( s );

#ifdef DBGPRN_ENABLED
  const int n1 = 0x01020304;
  const char* p1 = ( const char* ) &n1;
#endif /* DBGPRN_ENABLED */

  LGGM_PRINT_HEX ( p1, sizeof ( n1 ) );

#ifdef DBGPRN_ENABLED
  const int n2 = 0x04030201;
  const char* p2 = ( const char* ) &n2;
#endif /* DBGPRN_ENABLED */

  LGGM_PRINT_HEX ( p2, sizeof ( n2 ) );

  LGGM_CALL_OUT();
}

/*---------------------------------------------------------------------------*/

int main ( int argc, char** argv )
{
  ( void ) argc;
  ( void ) argv;

  LGGM_CALL_IN();

  doCLggmTest();

  LGGM_CALL_OUT();

  return 0;
}
