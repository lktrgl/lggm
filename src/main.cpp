#include "lggm/lggm.h"

#include <cstdint>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

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
#ifdef LGGM_MACRO_TESTS
  LS();
  LT();
  int a = 3;
  L ( a );
  std::string s = "s";
  L ( s );
  LM ( "a" );
  LT();
  LSS ( "this is a int: " << a << " this is a string: " << s );
  LT();

  {
    std::stringstream filecontents;

    {
      std::ifstream logfile ( lggm::lggm::getOutFileName(), std::ios::in );
      assert ( logfile.is_open() );

      do
      {
        std::string s;
        std::getline ( logfile, s );

        if ( logfile.fail() )
        {
          break;
        }

        filecontents << s << std::endl;
      }
      while ( logfile.good() );
    }

    std::cout << filecontents.str() <<  std::endl;
  }
#endif // LGGM_MACRO_TESTS
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
