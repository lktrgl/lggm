cmake_minimum_required(VERSION 3.5)

project ( Lggm )

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

if(NOT IS_SUBPROJECT)
    set ( CMAKE_C_STANDARD 99 )
    set ( CMAKE_CXX_STANDARD 17 )
    set ( CMAKE_C_FLAGS "-Wall -g3 -o0" )
    set ( CMAKE_CXX_FLAGS "-Wall -g3 -o0" )
    set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lstdc++ -lstdc++fs" )
endif()

include_directories (
     include
     )

add_library ( lggm
     include/lggm/lggm.h
     include/lggm/lggm.h
     include/lggm/dbgprn.h
     src/lggm/dbgprn.c
     )

if(NOT IS_SUBPROJECT)
    add_executable ( lggm_test
         src/main.cpp
         )

    target_link_libraries(lggm_test
         lggm
         )
endif()
     
