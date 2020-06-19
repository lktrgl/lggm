#include "lggm/lggm.h"

#include <cstdint>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

void doDropLogFile()
{
  std::ofstream logfile ( lggm::lggm<std::ofstream>::getOutFileName(), std::ios::out | std::ios::trunc );
  assert ( logfile.is_open() );
}

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

void doMacroTest()
{
  LGGM_SS();
  LGGM_SF();

  LGGM_TS();
  LGGM_TF();

  int a = 3;

  LGGM_PS ( a );
  LGGM_PF ( a );

  std::string s = "s";

  LGGM_PS ( s );
  LGGM_PF ( s );

  LGGM_MS ( "Message to stdout" );
  LGGM_MF ( "Message to file" );

  LGGM_TS();
  LGGM_TF();

  std::vector const v = {1, 2, 3};

  LGGM_VS ( v );
  LGGM_VF ( v );

  int x0 = -3;
  int x1 = 4;
  int x2 = 7;

  LGGM_RS ( x0, x2, x1 );
  LGGM_RF ( x0, x2, x1 );

  double dx0 = -3.0;
  double dx1 = 4.0;
  double dx2 = 7.0;

  LGGM_RS ( dx0, dx2, dx1 );
  LGGM_RF ( dx0, dx2, dx1 );

}

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


int main ( int argc, char** argv )
{
  std::cout << __PRETTY_FUNCTION__ << " ->" << std::endl;

  doDropLogFile();

  doCppClassTest();
  doMacroTest();

  doCopyLogFileToStdout();

  std::cout << __PRETTY_FUNCTION__ << " <-" << std::endl;

  return 0;
}
