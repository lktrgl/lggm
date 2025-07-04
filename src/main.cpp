/* to enable tracing UNcomment the following line */
/*
#define LGGM_ENABLE_LOGGER
*/
#include "lggm/lggm.h"

/*---------------------------------------------------------------------------*/

#include <cstdint>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <tuple>

/*---------------------------------------------------------------------------*/

void doDropLogFile()
{
  std::ofstream logfile ( lggm::lggm<std::ofstream>::getOutFileName(), std::ios::out | std::ios::trunc );
  assert ( logfile.is_open() );
}

/*---------------------------------------------------------------------------*/

void doCopyLogFileToStdout()
{
  std::cout << __PRETTY_FUNCTION__ << " ->" << std::endl;

  std::ifstream logfile ( lggm::lggm<std::ofstream>::getOutFileName(), std::ios::in );

  std::string text;

  while ( std::getline ( logfile, text ) )
  {
    std::cout << text << std::endl;
  }

  std::cout << __PRETTY_FUNCTION__ << " <-" << std::endl;
}

/*---------------------------------------------------------------------------*/

void doMacroTest()
{
  // print a scope pair
  LGGM_SS();
  LGGM_SF();

  // print a trace point
  LGGM_TS();
  LGGM_TF();

#ifdef LGGM_ENABLE_LOGGER
  int a = 3;
#endif /* LGGM_ENABLE_LOGGER */

  // print an integer value
  LGGM_PS ( a );
  LGGM_PF ( a );

#ifdef LGGM_ENABLE_LOGGER
  std::string s = "s";
#endif /* LGGM_ENABLE_LOGGER */

  // print a string value
  LGGM_PS ( s );
  LGGM_PF ( s );

#ifdef LGGM_ENABLE_LOGGER
  std::string shex = "0123";
#endif /* LGGM_ENABLE_LOGGER */

  // print a hexadecimal string value
  LGGM_HS ( shex.data(), shex.length() );
  LGGM_HF ( shex.data(), shex.length() );

  enum class en : uint8_t
  {
    one = 3
  };

  // print an enumeration value
  LGGM_PS ( en::one );
  LGGM_PF ( en::one );

  // print a message
  LGGM_MS ( "Message to stdout" );
  LGGM_MF ( "Message to file" );

  // print a trace point
  LGGM_TS();
  LGGM_TF();

#ifdef LGGM_ENABLE_LOGGER
  std::vector const v = {1, 2, 3};
#endif /* LGGM_ENABLE_LOGGER */

  // print a vector-like value
  LGGM_VS ( v );
  LGGM_VF ( v );

#ifdef LGGM_ENABLE_LOGGER
  int x0 = -3;
  int x1 = 4;
  int x2 = 7;
#endif /* LGGM_ENABLE_LOGGER */

  // print an integer ruler
  LGGM_RS ( x0, x2, x1 );
  LGGM_RF ( x0, x2, x1 );

#ifdef LGGM_ENABLE_LOGGER
  double dx0 = -3.0;
  double dx1 = 4.0;
  double dx2 = 7.0;
#endif /* LGGM_ENABLE_LOGGER */

  // print a floating point ruler
  LGGM_RS ( dx0, dx2, dx1 );
  LGGM_RF ( dx0, dx2, dx1 );

#ifdef LGGM_ENABLE_LOGGER
  int a0 = -3;
  int a1 = 4;
  int a2 = 7;
  int b0 = -3;
  int b1 = 4;
  int b2 = 7;
#endif /* LGGM_ENABLE_LOGGER */

  // print an integer plane ruler
  LGGM_QS ( a0, a2, b0, b2, a1, b1 );
  LGGM_QF ( a0, a2, b0, b2, a1, b1 );

#ifdef LGGM_ENABLE_LOGGER
  double da0 = -3.0;
  double da1 = 4.0;
  double da2 = 7.0;
  double db0 = -3.0;
  double db1 = 4.0;
  double db2 = 7.0;
#endif /* LGGM_ENABLE_LOGGER */

  // print a floating point plane ruler
  LGGM_QS ( da0, da2, db0, db2, da1, db1 );
  LGGM_QF ( da0, da2, db0, db2, da1, db1 );

#ifdef LGGM_ENABLE_LOGGER
  std::tuple<int, double, std::string> tv {-4, 3.14, "str"};
#endif /* LGGM_ENABLE_LOGGER */

  // print an tuple value
  LGGM_PS ( tv );
  LGGM_PF ( tv );
}

/*---------------------------------------------------------------------------*/

void doCppClassTest()
{
  {
    lggm::lggm logger ( std::cout, __LINE__, __PRETTY_FUNCTION__ );

    logger.doScope ();
    logger.doMessage (  "Message to stdout" );
  }

  {
    std::ofstream ofs;
    lggm::lggm logger ( ofs, __LINE__, __PRETTY_FUNCTION__ );

    logger.doScope ();
    logger.doMessage (  "Message to file" );
  }

}

/*---------------------------------------------------------------------------*/

void doCppLggmTest()
{
  doDropLogFile();

  doCppClassTest();
  doMacroTest();

  doCopyLogFileToStdout();
}

/*---------------------------------------------------------------------------*/

int main ( int argc, char** argv )
{
  ( void ) argc;
  ( void ) argv;

  std::cout << __PRETTY_FUNCTION__ << " ->" << std::endl;

  doCppLggmTest();

  std::cout << __PRETTY_FUNCTION__ << " <-" << std::endl;

  return 0;
}
