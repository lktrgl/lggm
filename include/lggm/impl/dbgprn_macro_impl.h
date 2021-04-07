#ifndef DBGPRN_MACRO_IMPL_H_INCLUDED
#define DBGPRN_MACRO_IMPL_H_INCLUDED

#if defined(DBGPRN_ENABLED)

  #define LGGM_TRACE() do{ lggmDbg(__FUNCTION__, __LINE__, "trace"); }while(0);
  #define LGGM_TRACE_C(on) do{ if(on){lggmDbg(__FUNCTION__, __LINE__, "trace");} }while(0);

  #define LGGM_CALL_IN() do{ lggmDbg(__FUNCTION__, __LINE__, "->"); }while(0);
  #define LGGM_CALL_IN_C(on) do{ if(on){lggmDbg(__FUNCTION__, __LINE__, "->");} }while(0);

  #define LGGM_CALL_OUT() do{ lggmDbg(__FUNCTION__, __LINE__, "<-"); }while(0);
  #define LGGM_CALL_OUT_C(on) do{ if(on){lggmDbg(__FUNCTION__, __LINE__, "<-");} }while(0);

  #define LGGM_PRINT_MSG(txt) do{ lggmDbg(__FUNCTION__, __LINE__, txt); }while(0);
  #define LGGM_PRINT_MSG_C(on,txt) do{ if(on){lggmDbg(__FUNCTION__, __LINE__, txt);} }while(0);

  #define LGGM_PRINT_INT(var) do{ lggmDbg(__FUNCTION__, __LINE__, lggmDbgGetStrInt(#var, var)); }while(0);
  #define LGGM_PRINT_INT_C(on,var) do{ if(on){lggmDbg(__FUNCTION__, __LINE__, lggmDbgGetStrInt(#var, var));} }while(0);

  #define LGGM_PRINT_STR(var) do{ lggmDbg(__FUNCTION__, __LINE__, lggmDbgGetStrStr(#var, var)); }while(0);
  #define LGGM_PRINT_STR_C(on,var) do{ if(on){lggmDbg(__FUNCTION__, __LINE__, lggmDbgGetStrStr(#var, var));} }while(0);

  #define LGGM_PRINT_HEX(ptr,len) do{ lggmDbg(__FUNCTION__, __LINE__, lggmDbgGetHexStr(#ptr, ptr,len)); }while(0);
  #define LGGM_PRINT_HEX_C(on,ptr,len) do{ if(on){lggmDbg(__FUNCTION__, __LINE__, lggmDbgGetHexStr(#ptr, ptr,len));} }while(0);

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
  #define LGGM_PRINT_STR(var)
  #define LGGM_PRINT_STR_C(on,var)
  #define LGGM_PRINT_HEX(ptr,len)
  #define LGGM_PRINT_HEX_C(on,ptr,len)

#endif

#endif /* DBGPRN_MACRO_IMPL_H_INCLUDED */
