#ifndef DBGPRN_IMPL_H_INCLUDED
#define DBGPRN_IMPL_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef DBGPRN_HEADER_BASED_ENABLED
void lggmDbg ( const char* function, int line, const char* message );

const char* lggmDbgGetStrInt ( const char* name, int val, char* buff );

const char* lggmDbgGetStrStr ( const char* name, const char* val, char* buff );

const char* lggmDbgGetHexStr ( const char* name, const char* ptr, int len, char* buff );
#endif /*DBGPRN_HEADER_BASED_ENABLED*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* DBGPRN_IMPL_H_INCLUDED */
