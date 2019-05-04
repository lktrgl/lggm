#include "lggm/lggm.h"

#include <cstdint>
#include <iostream>
#include <string>


int main ( int argc, char** argv )
{
  std::cout << __PRETTY_FUNCTION__ << " ->" << std::endl;

  LS();
  LT();
  int a = 3;
  L ( a );
  std::string s = "s";
  L ( s );
  LM ( "a" );
  LT();

  std::cout << __PRETTY_FUNCTION__ << " <-" << std::endl;

  return 0;
}
