#ifndef DBGPRN_C_INCLUDED
#define DBGPRN_C_INCLUDED

/*---------------------------------------------------------------------------*/

#include <lggm/dbgprn.h>

#include <lggm/impl/dbgprn_cfg.h>

#include <lggm/versions/version_info_lggm.h>

/*---------------------------------------------------------------------------*/

#include <time.h>
#include <stdio.h>
#include <string.h>

/*---------------------------------------------------------------------------*/

#ifdef DBGPRN_HEADER_BASED_ENABLED
  static inline
#endif
void lggmDbg ( const char* function, int line, const char* message )
{
#ifdef DBGPRN_ENABLED
  const char* s_File = "/var/tmp/dbgprn.log";
  FILE* out = NULL;

  if ( ( out = fopen ( s_File, "at" ) ) )
  {
    char timeStamptBuff[64];
    time_t result = time ( NULL );
    struct tm* locTime = localtime (&result );
    strftime ( timeStamptBuff, sizeof timeStamptBuff, "%Y-%m-%d %H:%M:%S", locTime );
    fprintf ( out, "%s %s:%d %s\n",
              timeStamptBuff,
              function,
              line,
              message );
    fclose ( out );
  }

#else /*DBGPRN_ENABLED*/
  ( void ) function;
  ( void ) line;
  ( void ) message;
#endif /*DBGPRN_ENABLED*/
}

/*---------------------------------------------------------------------------*/

#ifdef DBGPRN_HEADER_BASED_ENABLED
  static inline
#endif
void lggmDbgStdout ( const char* function, int line, const char* message )
{
#ifdef DBGPRN_ENABLED

  {
    char timeStamptBuff[64];
    time_t result = time ( NULL );
    struct tm* locTime = localtime (&result );
    strftime ( timeStamptBuff, sizeof timeStamptBuff, "%Y-%m-%d %H:%M:%S", locTime );
    printf ( "%s %s:%d %s\n",
             timeStamptBuff,
             function,
             line,
             message );
  }

#else /*DBGPRN_ENABLED*/
  ( void ) function;
  ( void ) line;
  ( void ) message;
#endif /*DBGPRN_ENABLED*/
}

/*---------------------------------------------------------------------------*/

#ifdef DBGPRN_HEADER_BASED_ENABLED
  static inline
#endif
const char* lggmDbgGetStrInt ( const char* name, int val, char* buff )
{
#ifdef DBGPRN_ENABLED
  sprintf ( buff, "%s=%d", name, val );
#else /*DBGPRN_ENABLED*/
  ( void ) name;
  ( void ) val;
#endif /*DBGPRN_ENABLED*/
  return buff;
}

/*---------------------------------------------------------------------------*/

#ifdef DBGPRN_HEADER_BASED_ENABLED
  static inline
#endif
const char* lggmDbgGetStrStrN ( const char* name, const char* val, int len, char* buff )
{
#ifdef DBGPRN_ENABLED
  size_t first_len = 0;
  sprintf ( buff, "%s='", name );
  first_len = strlen ( buff );

  while ( len-- )
  {
    * ( buff + first_len++ ) = *val++;
  }

  * ( buff + first_len ) = 0x00;
  strcat ( buff, "'" );
#else /*DBGPRN_ENABLED*/
  ( void ) name;
  ( void ) val;
  ( void ) len;
#endif /*DBGPRN_ENABLED*/
  return buff;
}

/*---------------------------------------------------------------------------*/

#ifdef DBGPRN_HEADER_BASED_ENABLED
  static inline
#endif
const char* lggmDbgGetStrStr ( const char* name, const char* val, char* buff )
{
#ifdef DBGPRN_ENABLED
  sprintf ( buff, "%s='%s'", name, val );
#else /*DBGPRN_ENABLED*/
  ( void ) name;
  ( void ) val;
#endif /*DBGPRN_ENABLED*/
  return buff;
}

/*---------------------------------------------------------------------------*/

#ifdef DBGPRN_HEADER_BASED_ENABLED
  static inline
#endif
const char* lggmDbgGetHexStr ( const char* name, const char* ptr, int len, char* buff )
{
#ifdef DBGPRN_ENABLED
  int first_byte = 1;
  size_t buff_len = 0;
  buff_len += sprintf (&buff[buff_len], "%s='", name );

  for ( int i = 0; len; ++i, --len )
  {
    buff_len += sprintf (&buff[buff_len], ( ( first_byte ) ? ( first_byte = 0, "%02X" ) : ( ":%02X" ) ),
                         ( unsigned char ) ptr[i] );
  }

  buff_len += sprintf (&buff[buff_len], "'" );

#else /*DBGPRN_ENABLED*/
  ( void ) name;
  ( void ) ptr;
  ( void ) len;
#endif /*DBGPRN_ENABLED*/
  return buff;
}

/*---------------------------------------------------------------------------*/

#ifdef DBGPRN_HEADER_BASED_ENABLED
  static inline
#endif
const char* lggmDbgVersion ( char* buffer, int buffer_len )
{
  const size_t string_length = ( size_t ) ( buffer_len - 1 ) < version_info_lggm_txt_len
                               ? ( size_t ) ( buffer_len - 1 )
                               : version_info_lggm_txt_len;

  if ( buffer_len == 0 || version_info_lggm_txt_len == 0 )
  {
    return NULL;
  }

  strncpy ( buffer, ( const char* ) version_info_lggm_txt, string_length );
  buffer[string_length] = '\0';

  return buffer;
}

/*---------------------------------------------------------------------------*/

#endif /* DBGPRN_C_INCLUDED */
