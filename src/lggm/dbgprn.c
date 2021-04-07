#include <lggm/dbgprn.h>

#include <lggm/impl/dbgprn_cfg.h>

#include <time.h>
#include <stdio.h>


void lggmDbg ( const char* function, int line, const char* message )
{
#if defined(DBGPRN_ENABLED)
  static const char* s_File = "/var/tmp/dbgprn.log";
  FILE* out = NULL;

  if ( ( out = fopen ( s_File, "at" ) ) )
  {
    char timeStamptBuff[64];
    time_t result = time ( NULL );
    struct tm* locTime = localtime ( &result );
    strftime ( timeStamptBuff, sizeof timeStamptBuff, "%Y-%m-%d %H:%M:%S", locTime );
    fprintf ( out, "%s %s:%d %s\n",
              timeStamptBuff,
              function,
              line,
              message );
    fclose ( out );
  }

#else
  ( void ) function;
  ( void ) line;
  ( void ) message;
#endif
}

const char* lggmDbgGetStrInt ( const char* name, int val )
{
  enum { bufflen = 128};
  static char buff[bufflen];
#if defined(DBGPRN_ENABLED)
  sprintf ( buff, "%s=%d", name, val );
#else
  ( void ) name;
  ( void ) val;
#endif
  return buff;
}

const char* lggmDbgGetStrStr ( const char* name, const char* val )
{
  enum { bufflen = 1024};
  static char buff[bufflen];
#if defined(DBGPRN_ENABLED)
  sprintf ( buff, "%s='%s'", name, val );
#else
  ( void ) name;
  ( void ) val;
#endif
  return buff;
}

const char* lggmDbgGetHexStr ( const char* name, const char* ptr, int len )
{
  enum { bufflen = 1024};
  static char buff[bufflen];
#if defined(DBGPRN_ENABLED)
  int first_byte = 1;
  size_t buff_len = 0;
  buff_len += sprintf ( &buff[buff_len], "%s='", name );

  for ( int i = 0; len; ++i, --len )
  {
    buff_len += sprintf ( &buff[buff_len], ( ( first_byte ) ? ( first_byte = 0, "%02X" ) : ( ":%02X" ) ),
                          ( unsigned char ) ptr[i] );
  }

  buff_len += sprintf ( &buff[buff_len], "'" );

#else
  ( void ) name;
  ( void ) ptr;
  ( void ) len;
#endif
  return buff;
}
