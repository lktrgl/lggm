#ifndef DBGPRN_IMPL_H_INCLUDED
#define DBGPRN_IMPL_H_INCLUDED

/*---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
{
#endif

/*---------------------------------------------------------------------------*/

#ifndef DBGPRN_HEADER_BASED_ENABLED

void lggmDbg ( const char* function, int line, const char* message );

void lggmDbgStdout ( const char* function, int line, const char* message );

const char* lggmDbgGetStrInt ( const char* name, int val, char* buff, int buff_len );

const char* lggmDbgGetStrStrN ( const char* name, const char* val, int len, char* buff, int buff_len );

const char* lggmDbgGetStrStr ( const char* name, const char* val, char* buff, int buff_len );

const char* lggmDbgGetHexStr ( const char* name, const char* ptr, int len, char* buff, int buff_len );

const char* lggmDbgVersion ( char* buffer, int buffer_len );

const char* lggmDbgGetIntRuleStr ( int a, int b, int x, char* buff, int buff_len );

const char* lggmDbgGetIntSquareStr ( int a, int b, int c, int d, int x, int y, char* buff, int buff_len );

#endif /*DBGPRN_HEADER_BASED_ENABLED*/

/*---------------------------------------------------------------------------*/

#ifdef __cplusplus
} /* extern "C" */

#endif

/*---------------------------------------------------------------------------*/

#endif /* DBGPRN_IMPL_H_INCLUDED */
