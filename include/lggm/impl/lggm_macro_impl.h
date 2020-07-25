#pragma once

#include <iostream>
#include <fstream>

#define LGGM_CAT(a,b) LGGM_CAT2(a, b)
#define LGGM_CAT2(a,b) a ## b

// stream to std::cout

#define LGGM_SS() lggm::lggm LGGM_CAT(LGGM_a, __LINE__) ( std::cout, __LINE__, __PRETTY_FUNCTION__ ) ; LGGM_CAT(LGGM_a, __LINE__).doScope ()

#define LGGM_TS() lggm::lggm ( std::cout, __LINE__, __PRETTY_FUNCTION__ ).doMessage ("trace")

#define LGGM_MS(m) lggm::lggm ( std::cout, __LINE__, __PRETTY_FUNCTION__ ).doMessage ( m )

#define LGGM_PS(v) lggm::lggm ( std::cout, __LINE__, __PRETTY_FUNCTION__ ).doNameValue ( #v , v )

#define LGGM_VS(v) lggm::lggm ( std::cout, __LINE__, __PRETTY_FUNCTION__ ).doVectorNameValue ( #v , v )

#define LGGM_RS(a, b, v) lggm::lggm<decltype(std::cout)>( std::cout, __LINE__, __PRETTY_FUNCTION__ ).doRuler<lggm::g_defaultRullerWidth>( a, b, #v , v )

#define LGGM_QS(a1, b1, a2, b2, v1, v2) lggm::lggm<decltype(std::cout)>( std::cout, __LINE__, __PRETTY_FUNCTION__ ).doPlaneRuler<lggm::g_defaultRullerWidth>( a1, b1, a2, b2, #v1, v1, #v2, v2 )

// output to the log file

#define LGGM_SF() std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm LGGM_CAT(LGGM_a, __LINE__) ( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, __PRETTY_FUNCTION__ ) ; LGGM_CAT(LGGM_a, __LINE__).doScope ()

#define LGGM_TF() std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm ( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, __PRETTY_FUNCTION__ ).doMessage ("trace")

#define LGGM_MF(m) std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm ( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, __PRETTY_FUNCTION__ ).doMessage ( m )

#define LGGM_PF(v) std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm ( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, __PRETTY_FUNCTION__ ).doNameValue ( #v , v )

#define LGGM_VF(v) std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm ( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, __PRETTY_FUNCTION__ ).doVectorNameValue ( #v , v )

#define LGGM_RF(a, b, v) std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm<decltype(LGGM_CAT(LGGM_afs, __LINE__))>( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, __PRETTY_FUNCTION__ ).doRuler<lggm::g_defaultRullerWidth>( a, b, #v , v )

#define LGGM_QF(a1, b1, a2, b2, v1, v2) std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm<decltype(LGGM_CAT(LGGM_afs, __LINE__))>( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, __PRETTY_FUNCTION__ ).doPlaneRuler<lggm::g_defaultRullerWidth>( a1, b1, a2, b2, #v1, v1, #v2, v2 )
