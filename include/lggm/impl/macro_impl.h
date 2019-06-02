#pragma once

#define LGGM_CAT(a,b) LGGM_CAT2(a, b)
#define LGGM_CAT2(a,b) a ## b

#define LS() lggm::lggm LGGM_CAT(a, __LINE__) ; LGGM_CAT(a, __LINE__).doScope ( __LINE__, __PRETTY_FUNCTION__ )

#define LT() lggm::lggm().doMessage ( __LINE__, __PRETTY_FUNCTION__ , "trace")

#define LM(m) lggm::lggm().doMessage ( __LINE__, __PRETTY_FUNCTION__ , m )

#define L(v) lggm::lggm().doNameValue ( __LINE__, __PRETTY_FUNCTION__ , #v , v )

#define LSS(v) lggm::lggm().doStream ( __LINE__, __PRETTY_FUNCTION__ ) << v
