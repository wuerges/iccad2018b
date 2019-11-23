cmake_minimum_required(VERSION 3.0)
project(iccad2018b CXX)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set (CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Ofast -march=native")

find_package(Boost COMPONENTS system filesystem REQUIRED)
IF (Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
  ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

find_package(Cairomm)
include_directories(${Cairomm_PKGCONF_INCLUDE_DIRS})

# RapidCheck will be built either as a static or a dynamic library depending on the CMake global
# variable BUILD_SHARED_LIBS (https://cmake.org/cmake/help/latest/variable/BUILD_SHARED_LIBS.html).
# If you wish to change the library type of RapidCheck, you can either specify the variable when invoking CMake
# or, if you are including RapidCheck as a subdirectory and wish to control the library type, you can set
# the variable before the call to add_subdirectory and reset it afterwards, if necessary.

include_directories( include )

add_subdirectory("ext-libs/cad_geometry")
add_library(libs
  src/parser.cxx  
  src/solver.cxx
  src/result.cxx
  src/astar.cxx
  src/global.cxx
  )

IF(EXISTS "${PROJECT_SOURCE_DIR}/ext-libs/rapidcheck/CMakeLists.txt")
  add_subdirectory("ext-libs/rapidcheck")
  add_subdirectory(test)
ENDIF()

add_executable(Report app/report.cxx)
target_link_libraries(Report
    libs
    cadgeometry
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  )

add_executable(Draw app/draw.cxx)
target_link_libraries(Draw
    libs
  ${Boost_FILESYSTEM_LIBRARY}
  ${Cairomm_LIBRARIES}
  ${Boost_SYSTEM_LIBRARY}
  )

add_executable(Solver app/solver.cxx)
target_link_libraries(Solver
    libs
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  )
