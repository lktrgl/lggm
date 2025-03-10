#ifndef DBGPRN_MACRO_IMPL_H_INCLUDED
#define DBGPRN_MACRO_IMPL_H_INCLUDED

/*---------------------------------------------------------------------------*/

#if defined(DBGPRN_ENABLED)

  #if defined(DBGPRN_TO_STDOUT)
    #define DBGPRN_ENGINE lggmDbgStdout
  #else
    #define DBGPRN_ENGINE lggmDbg
  #endif

  #define LGGM_TRACE() do{ DBGPRN_ENGINE(__FUNCTION__, __LINE__, "trace"); }while(0);
  #define LGGM_TRACE_C(on) do{ if(on){DBGPRN_ENGINE(__FUNCTION__, __LINE__, "trace");} }while(0);

  #define LGGM_CALL_IN() do{ DBGPRN_ENGINE(__FUNCTION__, __LINE__, "->"); }while(0);
  #define LGGM_CALL_IN_C(on) do{ if(on){DBGPRN_ENGINE(__FUNCTION__, __LINE__, "->");} }while(0);

  #define LGGM_CALL_OUT() do{ DBGPRN_ENGINE(__FUNCTION__, __LINE__, "<-"); }while(0);
  #define LGGM_CALL_OUT_C(on) do{ if(on){DBGPRN_ENGINE(__FUNCTION__, __LINE__, "<-");} }while(0);

  #define LGGM_PRINT_MSG(txt) do{ DBGPRN_ENGINE(__FUNCTION__, __LINE__, txt); }while(0);
  #define LGGM_PRINT_MSG_C(on,txt) do{ if(on){DBGPRN_ENGINE(__FUNCTION__, __LINE__, txt);} }while(0);

  #define LGGM_PRINT_INT(var) do{ enum{LGGM_buff_len=1024};char LGGM_buff[LGGM_buff_len];DBGPRN_ENGINE(__FUNCTION__, __LINE__, lggmDbgGetStrInt(#var, var,LGGM_buff)); }while(0);
  #define LGGM_PRINT_INT_C(on,var) do{ if(on){enum{LGGM_buff_len=1024};char LGGM_buff[LGGM_buff_len];DBGPRN_ENGINE(__FUNCTION__, __LINE__, lggmDbgGetStrInt(#var, var,LGGM_buff));} }while(0);

  #define LGGM_PRINT_STR_N(var,len) do{ enum{LGGM_buff_len=1024};char LGGM_buff[LGGM_buff_len];DBGPRN_ENGINE(__FUNCTION__, __LINE__, lggmDbgGetStrStrN(#var,var,len,LGGM_buff)); }while(0);
  #define LGGM_PRINT_STR_N_C(on,var,len) do{ if(on){enum{LGGM_buff_len=1024};char LGGM_buff[LGGM_buff_len];DBGPRN_ENGINE(__FUNCTION__, __LINE__, lggmDbgGetStrStrN(#var,var,len,LGGM_buff));} }while(0);

  #define LGGM_PRINT_STR(var) do{ enum{LGGM_buff_len=1024};char LGGM_buff[LGGM_buff_len];DBGPRN_ENGINE(__FUNCTION__, __LINE__, lggmDbgGetStrStr(#var, var,LGGM_buff)); }while(0);
  #define LGGM_PRINT_STR_C(on,var) do{ if(on){enum{LGGM_buff_len=1024};char LGGM_buff[LGGM_buff_len];DBGPRN_ENGINE(__FUNCTION__, __LINE__, lggmDbgGetStrStr(#var, var,LGGM_buff));} }while(0);

  #define LGGM_PRINT_HEX(ptr,len) do{ enum{LGGM_buff_len=1024};char LGGM_buff[LGGM_buff_len];DBGPRN_ENGINE(__FUNCTION__, __LINE__, lggmDbgGetHexStr(#ptr, ((const char*)(ptr)), len,LGGM_buff)); }while(0);
  #define LGGM_PRINT_HEX_C(on,ptr,len) do{ if(on){enum{LGGM_buff_len=1024};char LGGM_buff[LGGM_buff_len];DBGPRN_ENGINE(__FUNCTION__, __LINE__, lggmDbgGetHexStr(#ptr, ((const char*)(ptr)), len,LGGM_buff));} }while(0);

#else

  #define LGGM_TRACE()
  #define LGGM_TRACE_C(on)
  #define LGGM_CALL_IN()
  #define LGGM_CALL_IN_C(on)
  #define LGGM_CALL_OUT()
  #define LGGM_CALL_OUT_C(on)
  #define LGGM_PRINT_MSG(txt)
  #define LGGM_PRINT_MSG_C(on,txt)
  #define LGGM_PRINT_INT(var)
  #define LGGM_PRINT_INT_C(on,var)
  #define LGGM_PRINT_STR_N(var,len)
  #define LGGM_PRINT_STR_N_C(on,var,len)
  #define LGGM_PRINT_STR(var)
  #define LGGM_PRINT_STR_C(on,var)
  #define LGGM_PRINT_HEX(ptr,len)
  #define LGGM_PRINT_HEX_C(on,ptr,len)

#endif

/*---------------------------------------------------------------------------*/

#endif /* DBGPRN_MACRO_IMPL_H_INCLUDED */
