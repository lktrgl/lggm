#include "lggm/lggm.h"

#include <cstdint>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>


int main ( int argc, char** argv )
{
  std::cout << __PRETTY_FUNCTION__ << " ->" << std::endl;

  {
    std::ofstream logfile ( lggm::lggm::getOutFileName(), std::ios::out | std::ios::trunc );
    assert ( logfile.is_open() );
  }

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

  std::cout << __PRETTY_FUNCTION__ << " <-" << std::endl;

  return 0;
}
