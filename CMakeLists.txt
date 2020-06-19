cmake_minimum_required(VERSION 3.5)

project ( Lggm )

set ( CMAKE_CXX_STANDARD 17 )
set ( CMAKE_C_FLAGS "-Wall -g3 -o0" )
set ( CMAKE_CXX_FLAGS "-Wall -g3 -o0" )
set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lstdc++ -lstdc++fs" )

include_directories (
     include
     )

add_executable ( LggmTest
     src/main.cpp
     include/lggm/lggm.h
     )
