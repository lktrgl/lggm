#pragma once

#define LGGM_CAT(a,b) LGGM_CAT2(a, b)
#define LGGM_CAT2(a,b) a ## b

// stream to std::cout

#define LGGM_SS() lggm::lggm LGGM_CAT(LGGM_a, __LINE__) ( std::cout, __LINE__, __PRETTY_FUNCTION__ ) ; LGGM_CAT(LGGM_a, __LINE__).doScope ()

#define LGGM_TS() lggm::lggm ( std::cout, __LINE__, __PRETTY_FUNCTION__ ).doMessage ("trace")

#define LGGM_MS(m) lggm::lggm ( std::cout, __LINE__, __PRETTY_FUNCTION__ ).doMessage ( m )

#define LGGM_PS(v) lggm::lggm ( std::cout, __LINE__, __PRETTY_FUNCTION__ ).doNameValue ( #v , v )

// output to the log file

#define LGGM_SF() std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm LGGM_CAT(LGGM_a, __LINE__) ( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, __PRETTY_FUNCTION__ ) ; LGGM_CAT(LGGM_a, __LINE__).doScope ()

#define LGGM_TF() std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm ( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, __PRETTY_FUNCTION__ ).doMessage ("trace")

#define LGGM_MF(m) std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm ( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, __PRETTY_FUNCTION__ ).doMessage ( m )

#define LGGM_PF(v) std::ofstream LGGM_CAT(LGGM_afs, __LINE__); lggm::lggm ( LGGM_CAT(LGGM_afs, __LINE__), __LINE__, __PRETTY_FUNCTION__ ).doNameValue ( #v , v )
