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
  LGGM_CALL_IN_C ( 1 );

  LGGM_PRINT_MSG ( "before trace" );
  LGGM_PRINT_MSG_C ( 1, "before trace" );
  LGGM_TRACE();
  LGGM_TRACE_C ( 1 );

#ifdef DBGPRN_ENABLED
  int a = 7;
#endif /* DBGPRN_ENABLED */

  LGGM_PRINT_INT ( a );
  LGGM_PRINT_INT_C ( 1, a );

#ifdef DBGPRN_ENABLED
  const char* s = "a string";
#endif /* DBGPRN_ENABLED */

  LGGM_PRINT_STR_N ( s, 5 );
  LGGM_PRINT_STR_N_C ( 1, s, 5 );

  LGGM_PRINT_STR ( s );
  LGGM_PRINT_STR_C ( 1, s );

#ifdef DBGPRN_ENABLED
  const int n1 = 0x01020304;
  const char* p1 = ( const char* ) &n1;
#endif /* DBGPRN_ENABLED */

  LGGM_PRINT_HEX ( p1, sizeof ( n1 ) );
  LGGM_PRINT_HEX_C ( 1, p1, sizeof ( n1 ) );

  LGGM_CALL_OUT();
  LGGM_CALL_OUT_C ( 1 );
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
