cmake_minimum_required(VERSION 2.6)
project( eigen2mat CXX )

# Set those variable if CMake is not able to find Matlab & Eigen
#set( MATLAB_ROOT "C:\\Program Files\\MATLAB\\R2012b" )
#  eigen directory should contain the 'signature_of_eigen3_matrix_library' file
#set( CMAKE_PREFIX_PATH "path/to/eigen" )
#set( CMAKE_PREFIX_PATH "D:\\Nguyen\\mex_files\\protection\\eigen-3.2.0" )

# Project defines (can be modified)
# add_definitions( -DEIGEN2MAT_TYPE_CHECK )
# add_definitions( -DEIGEN2MAT_RANGE_CHECK )

# ==============================================================================
#                                                                              #
# Below this point, everything should be fine whatever the configuration       #
#                                                                              #
# ==============================================================================

# Compiler flags
set( CMAKE_CXX_FLAGS "-std=c++11" )

set( CLANG_CXXFLAGS "-Weverything -Wno-c++98-compat -Wno-missing-prototypes" )
set( CLANG_CXXFLAGS "${CLANG_CXXFLAGS} -stdlib=libc++ -fPIC" )

set ( GCC_CXXFLAGS "-Wall -Wextra -ansi -pedantic -Wshadow -Wfloat-equal" )
set ( GCC_CXXFLAGS "${GCC_CXXFLAGS} -Wctor-dtor-privacy -Wnon-virtual-dtor" )
set ( GCC_CXXFLAGS "${GCC_CXXFLAGS} -Woverloaded-virtual -Wmissing-include-dirs" )
set ( GCC_CXXFLAGS "${GCC_CXXFLAGS} -Wconversion -Wwrite-strings -Wold-style-cast" )
set ( GCC_CXXFLAGS "${GCC_CXXFLAGS} -Wpointer-arith -Wcast-qual -Wcast-align" )
set ( GCC_CXXFLAGS "${GCC_CXXFLAGS} -Wswitch-enum -Wundef -Wredundant-decls" )
set ( GCC_CXXFLAGS "${GCC_CXXFLAGS} -Wstrict-null-sentinel -Wwrite-strings" )
set ( GCC_CXXFLAGS "${GCC_CXXFLAGS} -Wunreachable-code -Wno-unknown-pragmas" )
set ( GCC_CXXFLAGS "${GCC_CXXFLAGS} -Weffc++ -fPIC" )

set( MSVC_CXXFLAGS "/W3" )

# ==============================================================================
# Check which compiler we are dealing with and check its version
if( NOT MSVC )
  execute_process( COMMAND ${CMAKE_CXX_COMPILER} -v
    ERROR_VARIABLE _compiler_output )
endif( NOT MSVC )

# ======================================

set( IS_GCC 0 )
set( IS_CLANG 0 )

if ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" )
  set( IS_GCC 1 )
  set( CMAKE_CXX_FLAGS "${GCC_CXXFLAGS} ${CMAKE_CXX_FLAGS}" )
  string(REGEX REPLACE ".* ([0-9]\\.[0-9]\\.[0-9]) .*" "\\1"
    COMPILER_VERSION ${_compiler_output})

elseif ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )
  set( IS_CLANG 1 )
  string(REGEX REPLACE ".* ([0-9]\\.[0-9]) .*" "\\1"
    COMPILER_VERSION ${_compiler_output})

  if ( ${COMPILER_VERSION} VERSION_GREATER 3.2 )
    set( CLANG_CXXFLAGS "${CLANG_CXXFLAGS} -Wno-documentation-deprecated-sync" )
    set( CLANG_CXXFLAGS "${CLANG_CXXFLAGS} -Wno-documentation" )
  endif()
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_CXXFLAGS}" )

elseif ( MSVC )
  set( CMAKE_CXX_FLAGS "${MSVC_CXXFLAGS}" )
  add_definitions( -D_SCL_SECURE_NO_WARNINGS )
  if (MSVC_VERSION LESS 1600)
    set( COMPILER_VERSION "1900" )

  elseif (MSVC_VERSION EQUAL 1600)
    set( COMPILER_VERSION "2010" )

  elseif (MSVC_VERSION EQUAL 1700)
    set( COMPILER_VERSION "2011" )

  elseif (MSVC_VERSION EQUAL 1800)
    set( COMPILER_VERSION "2012" )

  elseif (MSVC_VERSION EQUAL 1900)
    set( COMPILER_VERSION "2013" )

  elseif (MSVC_VERSION GREATER 1900)
    set( COMPILER_VERSION "3000" )

  endif (MSVC_VERSION LESS 1600)

else ()
  message( FATAL_ERROR "Unkown compiler -> does not know which flag to use..." )

endif()

message(STATUS "C++ compiler version: ${COMPILER_VERSION} [${CMAKE_CXX_COMPILER}]")

# ======================================
# Set Release/Debug compile flags

if( NOT MSVC )
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -DNDEBUG -O2")
else( NOT MSVC )
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} /Od /Ob0")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -DNDEBUG /O2 /Ot /GL /Oi")
endif( NOT MSVC )

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RELEASE CACHE STRING
      "Choose the type of build, options are: None, Debug, Release (default)."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)
message(STATUS "Build type is: ${CMAKE_BUILD_TYPE}")

# ======================================

if( IS_GCC AND COMPILER_VERSION VERSION_LESS "4.7")
  message( FATAL_ERROR "This project requires at least GCC-4.7.x" )

elseif( IS_CLANG AND COMPILER_VERSION VERSION_LESS "3.1")
  message( FATAL_ERROR "This project requires at least clang-3.1" )

elseif( IS_MSVC AND COMPILER_VERSION VERSION_LESS "2010")
  message( FATAL_ERROR "This project requires at least MSVC2010" )
endif()

# ==============================================================================

# Find out which git branch we are in
# execute_process( COMMAND git rev-parse --abbrev-ref HEAD
#   OUTPUT_VARIABLE git_branch_name 
#   OUTPUT_STRIP_TRAILING_WHITESPACE)

# ==============================================================================

set( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

find_package( Matlab2 REQUIRED )
if ( MATLAB_FOUND )
  message( STATUS "MATLAB root: ${MATLAB_ROOT}" )
  message( STATUS "MATLAB includes: ${MATLAB_INCLUDE_DIR}" )
  include_directories( ${MATLAB_INCLUDE_DIR} )
else( MATLAB_FOUND )
  message( FATAL_ERROR "Couldn't find MATLAB" )
endif( MATLAB_FOUND )

find_package( Eigen3 REQUIRED )
message( STATUS "Eigen3 includes: ${EIGEN3_INCLUDE_DIR}" )
include_directories( "${EIGEN3_INCLUDE_DIR}" )

# ==============================================================================
# Add sub-directories and include paths

include_directories( ${eigen2mat_SOURCE_DIR}/ )

# ==============================================================================
# Add doxygen target
find_package( Doxygen )
if( DOXYGEN_FOUND )
  set( DOC_OUTPUT_DIR "documentation" )
  configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in 
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY )
  add_custom_target( doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating documentation with Doxygen" VERBATIM
    )
  add_custom_target( clean_doc
    rm -rf ${DOC_OUTPUT_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Cleaning documentation" VERBATIM
    )
endif( DOXYGEN_FOUND )

# ==============================================================================

string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
message(STATUS "Executable output path: ${EXECUTABLE_OUTPUT_PATH}" )

add_library( eigen2mat_static STATIC
  src/conversion.cpp
  src/print.cpp
  src/tensor_to_matrix.cpp
  )
set_target_properties(
  eigen2mat_static 
  PROPERTIES 
  OUTPUT_NAME "eigen2matu"
  OUTPUT_NAME_DEBUG "eigen2matd"
  OUTPUT_NAME_RELEASE "eigen2mat"
  )

add_custom_command(
  TARGET eigen2mat_static
  PRE_LINK
  COMMAND echo "NOTE: linking library in ${CMAKE_BUILD_TYPE} mode"
  )

add_executable( mytest test/test.cpp )
target_link_libraries( mytest eigen2mat_static "${MATLAB_LIBRARIES}" )

enable_testing()
add_test( NAME dev-test COMMAND mytest )

# add_library( eigen2mat_shared SHARED
#   src/cpp/conversion.cpp
#   src/cpp/print.cpp
#   src/cpp/tensor_to_matrix.cpp
#   )

# target_link_libraries( eigen2mat_shared ${MATLAB_LIBRARIES} )
# set_target_properties(eigen2mat_shared PROPERTIES OUTPUT_NAME eigen2mat)

