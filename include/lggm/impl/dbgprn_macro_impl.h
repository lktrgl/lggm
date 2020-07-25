#ifndef DBGPRN_MACRO_IMPL_H_INCLUDED
#define DBGPRN_MACRO_IMPL_H_INCLUDED

#if defined(DBGPRN_ENABLED)

  #define LGGM_TRACE() do{ lggmDbg(__FUNCTION__, __LINE__, "trace"); }while(0);
  #define LGGM_CALL_IN() do{ lggmDbg(__FUNCTION__, __LINE__, "->"); }while(0);
  #define LGGM_CALL_OUT() do{ lggmDbg(__FUNCTION__, __LINE__, "<-"); }while(0);
  #define LGGM_PRINT_MSG(txt) do{ lggmDbg(__FUNCTION__, __LINE__, txt); }while(0);
  #define LGGM_PRINT_INT(var) do{ lggmDbg(__FUNCTION__, __LINE__, lggmDbgGetStrInt(#var, var)); }while(0);
  #define LGGM_PRINT_STR(var) do{ lggmDbg(__FUNCTION__, __LINE__, lggmDbgGetStrStr(#var, var)); }while(0);

#else

  #define LGGM_TRACE()
  #define LGGM_CALL_IN()
  #define LGGM_CALL_OUT()
  #define LGGM_PRINT_MSG(txt)
  #define LGGM_PRINT_INT(var)
  #define LGGM_PRINT_STR(var)

#endif

#endif /* DBGPRN_MACRO_IMPL_H_INCLUDED */
