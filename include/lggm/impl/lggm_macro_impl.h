#pragma once

#include <iostream>
#include <fstream>

#define LGGM_CAT(a,b) LGGM_CAT2(a, b)
#define LGGM_CAT2(a,b) a ## b

#define LGGM_FUNCTION_MACRO __PRETTY_FUNCTION__
//#define LGGM_FUNCTION_MACRO __FUNCTION__

// stream to std::cout

#ifdef LGGM_ENABLE_LOGGER

#define LGGM_SS() lggm::lggm<decltype(std::cout)> LGGM_CAT(LGGM_a, __LINE__) ( std::cout, __LINE__, LGGM_FUNCTION_MACRO ) ; LGGM_CAT(LGGM_a, __LINE__).doScope ()

#define LGGM_TS() lggm::lggm<decltype(std::cout)> ( std::cout, __LINE__, LGGM_FUNCTION_MACRO ).doMessage ("trace")

#define LGGM_MS(m) lggm::lggm<decltype(std::cout)> ( std::cout, __LINE__, LGGM_FUNCTION_MACRO ).doMessage ( m )

#define LGGM_PS(v) lggm::lggm<decltype(std::cout)> ( std::cout, __LINE__, LGGM_FUNCTION_MACRO ).doNameValue ( #v , v )

#define LGGM_VS(v) lggm::lggm<decltype(std::cout)> ( std::cout, __LINE__, LGGM_FUNCTION_MACRO ).doVectorNameValue ( #v , v )

#define LGGM_RS(a, b, v) lggm::lggm<decltype(std::cout)>( std::cout, __LINE__, LGGM_FUNCTION_MACRO ).doRuler<lggm::g_defaultRullerWidth>( a, b, #v , v )

#define LGGM_QS(a1, b1, a2, b2, v1, v2) lggm::lggm<decltype(std::cout)>( std::cout, __LINE__, LGGM_FUNCTION_MACRO ).doPlaneRuler<lggm::g_defaultRullerWidth>( a1, b1, a2, b2, #v1, v1, #v2, v2 )

// output to the log file

#define LGGM_SF() std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm LGGM_CAT(LGGM_a, __LINE__) ( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, LGGM_FUNCTION_MACRO ) ; LGGM_CAT(LGGM_a, __LINE__).doScope ()

#define LGGM_TF() std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm ( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, LGGM_FUNCTION_MACRO ).doMessage ("trace")

#define LGGM_MF(m) std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm ( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, LGGM_FUNCTION_MACRO ).doMessage ( m )

#define LGGM_PF(v) std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm ( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, LGGM_FUNCTION_MACRO ).doNameValue ( #v , v )

#define LGGM_VF(v) std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm ( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, LGGM_FUNCTION_MACRO ).doVectorNameValue ( #v , v )

#define LGGM_RF(a, b, v) std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm<decltype(LGGM_CAT(LGGM_afs, __LINE__))>( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, LGGM_FUNCTION_MACRO ).doRuler<lggm::g_defaultRullerWidth>( a, b, #v , v )

#define LGGM_QF(a1, b1, a2, b2, v1, v2) std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm<decltype(LGGM_CAT(LGGM_afs, __LINE__))>( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, LGGM_FUNCTION_MACRO ).doPlaneRuler<lggm::g_defaultRullerWidth>( a1, b1, a2, b2, #v1, v1, #v2, v2 )

#else

#define LGGM_SS()

#define LGGM_TS()

#define LGGM_MS(m)

#define LGGM_PS(v)

#define LGGM_VS(v)

#define LGGM_RS(a, b, v)

#define LGGM_QS(a1, b1, a2, b2, v1, v2)

// output to the log file

#define LGGM_SF()

#define LGGM_TF()

#define LGGM_MF(m)

#define LGGM_PF(v)

#define LGGM_VF(v)

#define LGGM_RF(a, b, v)

#define LGGM_QF(a1, b1, a2, b2, v1, v2)

#endif // LGGM_ENABLE_LOGGER
