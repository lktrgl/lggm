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
const char* lggmDbgGetStrInt ( const char* name, int val, char* buff, int buff_len )
{
#ifdef DBGPRN_ENABLED
  snprintf ( buff, buff_len, "%s=%d", name, val );
#else /*DBGPRN_ENABLED*/
  ( void ) buff_len;
  ( void ) name;
  ( void ) val;
#endif /*DBGPRN_ENABLED*/
  return buff;
}

/*---------------------------------------------------------------------------*/

#ifdef DBGPRN_HEADER_BASED_ENABLED
  static inline
#endif
const char* lggmDbgGetStrStrN ( const char* name, const char* val, int len, char* buff, int buff_len )
{
#ifdef DBGPRN_ENABLED
  size_t first_len = 0;
  buff_len -= snprintf ( buff, buff_len, "%s='", name );
  first_len = strlen ( buff );

  if ( buff_len < len )
  {
    len = buff_len;
  }

  while ( len-- )
  {
    * ( buff + first_len++ ) = *val++;
  }

  * ( buff + first_len ) = 0x00;
  strcat ( buff, "'" );
#else /*DBGPRN_ENABLED*/
  ( void ) buff_len;
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
const char* lggmDbgGetStrStr ( const char* name, const char* val, char* buff, int buff_len )
{
#ifdef DBGPRN_ENABLED
  snprintf ( buff, buff_len, "%s='%s'", name, val );
#else /*DBGPRN_ENABLED*/
  ( void ) buff_len;
  ( void ) name;
  ( void ) val;
#endif /*DBGPRN_ENABLED*/
  return buff;
}

/*---------------------------------------------------------------------------*/

#ifdef DBGPRN_HEADER_BASED_ENABLED
  static inline
#endif
const char* lggmDbgGetHexStr ( const char* name, const char* ptr, int len, char* buff, int buff_len )
{
#ifdef DBGPRN_ENABLED
  int first_byte = 1;
  size_t buff_offs = 0;
  buff_offs += snprintf (&buff[buff_offs], ( buff_len - buff_offs ), "%s='", name );

  for ( int i = 0; len; ++i, --len )
  {
    buff_offs += snprintf (&buff[buff_offs], ( buff_len - buff_offs ), ( ( first_byte ) ? ( first_byte = 0,
                           "%02X" ) : ( ":%02X" ) ),
                           ( unsigned char ) ptr[i] );
  }

  buff_offs += snprintf (&buff[buff_offs], ( buff_len - buff_offs ), "'" );

#else /*DBGPRN_ENABLED*/
  ( void ) buff_len;
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
#define LGGM_DBG_GET_INT_RULE_STR_WIDTH (15)
#ifdef DBGPRN_HEADER_BASED_ENABLED
  static inline
#endif
const char* lggmDbgGetIntRuleStr ( int a, int b, int x, char* buff, int buff_len )
{
#ifdef DBGPRN_ENABLED
  size_t buff_offs = 0;
  buff_offs += snprintf (&buff[buff_offs], ( buff_len - buff_offs ), "{%d,%d,%d}=[", a, b, x );

  const int position = ( int ) ( ( a > x )
                                 ? 0
                                 : ( ( b < x )
                                     ? ( LGGM_DBG_GET_INT_RULE_STR_WIDTH - 1 )
                                     : (
                                       ( a == b )
                                       ? 0
                                       : ( ( double ) ( x - a ) / ( double ) ( b - a ) * LGGM_DBG_GET_INT_RULE_STR_WIDTH )
                                     )
                                   )
                               );

  for ( int i = 0; i < LGGM_DBG_GET_INT_RULE_STR_WIDTH; ++i )
  {
    buff_offs += snprintf (&buff[buff_offs], ( buff_len - buff_offs ), ( ( i == position ) ? ( "*" ) : ( "-" ) ) );
  }

  buff_offs += snprintf (&buff[buff_offs], ( buff_len - buff_offs ), "]" );

#else /*DBGPRN_ENABLED*/
  ( void ) buff_len;
  ( void ) a;
  ( void ) b;
  ( void ) x;
#endif /*DBGPRN_ENABLED*/
  return buff;
}

#undef LGGM_DBG_GET_INT_RULE_STR_WIDTH

/*---------------------------------------------------------------------------*/
//#define DBGPRN_ENABLED

#define LGGM_DBG_GET_INT_SQR_STR_WIDTH (15)
#define LGGM_DBG_GET_INT_SQR_STR_HEIGHT (15)
#ifdef DBGPRN_HEADER_BASED_ENABLED
  static inline
#endif
const char* lggmDbgGetIntSquareStr ( int a, int b, int c, int d, int x, int y, char* buff, int buff_len )
{
#ifdef DBGPRN_ENABLED
  size_t buff_offs = 0;
  buff_offs += snprintf (&buff[buff_offs], ( buff_len - buff_offs ), "{%d,%d,%d}{%d,%d,%d}=\n", a, b, x, c, d, y );

  const int position_x = ( int ) ( ( a > x )
                                   ? 0
                                   : ( ( b < x )
                                       ? ( LGGM_DBG_GET_INT_SQR_STR_WIDTH - 1 )
                                       : (
                                         ( a == b )
                                         ? 0
                                         : ( ( double ) ( x - a ) / ( double ) ( b - a ) * LGGM_DBG_GET_INT_SQR_STR_WIDTH )
                                       )
                                     )
                                 );

  const int position_y = ( int ) ( ( c > y )
                                   ? 0
                                   : ( ( d < y )
                                       ? ( LGGM_DBG_GET_INT_SQR_STR_HEIGHT - 1 )
                                       : (
                                         ( c == d )
                                         ? 0
                                         : ( ( double ) ( y - c ) / ( double ) ( d - c ) * LGGM_DBG_GET_INT_SQR_STR_HEIGHT )
                                       )
                                     )
                                 );

  for ( int j = 0; j < LGGM_DBG_GET_INT_SQR_STR_WIDTH; ++j )
  {
    buff_offs += snprintf (&buff[buff_offs], ( buff_len - buff_offs ), "[" );

    for ( int i = 0; i < LGGM_DBG_GET_INT_SQR_STR_WIDTH; ++i )
    {
      buff_offs += snprintf (&buff[buff_offs], ( buff_len - buff_offs ), ( ( i == position_x &&
                             j == position_y ) ? ( "*" ) : ( "-" ) ) );
    }

    buff_offs += snprintf (&buff[buff_offs], ( buff_len - buff_offs ), "]\n" );
  }

#else /*DBGPRN_ENABLED*/
  ( void ) buff_len;
  ( void ) a;
  ( void ) b;
  ( void ) c;
  ( void ) d;
  ( void ) x;
  ( void ) y;
#endif /*DBGPRN_ENABLED*/
  return buff;
}

#undef LGGM_DBG_GET_INT_SQR_STR_WIDTH
#undef LGGM_DBG_GET_INT_SQR_STR_HEIGHT

/*---------------------------------------------------------------------------*/

#endif /* DBGPRN_C_INCLUDED */
