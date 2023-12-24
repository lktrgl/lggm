cmake_minimum_required(VERSION 3.5)

project ( Lggm )

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

if(NOT IS_SUBPROJECT)

    message(STATUS "this is not IS_SUBPROJECT")

    set ( CMAKE_C_STANDARD 99 )
    set ( CMAKE_CXX_STANDARD 20 )
    set ( CMAKE_C_FLAGS "-Wall -g3 -O0" )
    set ( CMAKE_CXX_FLAGS "-Wall -g3 -O0" )
    set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lstdc++ -lstdc++fs" )

else()

	message(STATUS "this is IS_SUBPROJECT")

	set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNDEBUG" )
	set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNDEBUG" )
endif()

    message(STATUS "CMAKE_C_STANDARD=[${CMAKE_C_STANDARD}]")
    message(STATUS "CMAKE_CXX_STANDARD=[${CMAKE_CXX_STANDARD}]")
    message(STATUS "CMAKE_C_FLAGS=[${CMAKE_C_FLAGS}]")
    message(STATUS "CMAKE_EXE_LINKER_FLAGS=[${CMAKE_EXE_LINKER_FLAGS}]")

include_directories (
     ${CMAKE_CURRENT_SOURCE_DIR}/include
     )

#
# declare autocreated folders and variables
#

set (lggm-hex-versions-dest-folder include/lggm/versions)
set (lggm-conv-util ${CMAKE_CURRENT_SOURCE_DIR}/script/conv/template_to_hex.sh)
set (lggm-get-version-util ${CMAKE_CURRENT_SOURCE_DIR}/script/version/get_component_version_info.sh)

#
# create the output folder
#

add_custom_target(lggm-build-time-make-directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/${lggm-hex-versions-dest-folder}
)

#
# get version info
#

add_custom_target(lggm-build-time-get-version-info ALL
    COMMAND ${lggm-get-version-util} ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${lggm-conv-util} ${CMAKE_CURRENT_SOURCE_DIR} version_info.txt "${lggm-hex-versions-dest-folder}/version_info.h"
)

#
# declare library contents
#

add_library ( lggm
     ${CMAKE_CURRENT_SOURCE_DIR}/include/lggm/lggm.h
     ${CMAKE_CURRENT_SOURCE_DIR}/include/lggm/lggm.h
     ${CMAKE_CURRENT_SOURCE_DIR}/include/lggm/dbgprn.h
     ${CMAKE_CURRENT_SOURCE_DIR}/src/lggm/dbgprn.c
     )

add_dependencies( lggm
    lggm-build-time-get-version-info
    )

add_dependencies( lggm-build-time-get-version-info
    lggm-build-time-make-directory
    )

set_target_properties( lggm
     PROPERTIES
          LINKER_LANGUAGE CXX
     )

if(NOT IS_SUBPROJECT)
    add_executable ( lggm_test
         ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
         )

    target_link_libraries(lggm_test
         lggm
         )
endif()
     
