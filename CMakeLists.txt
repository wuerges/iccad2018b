cmake_minimum_required(VERSION 3.15)
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

add_subdirectory("ext-libs/cad_geometry")

include_directories( include )

add_library(libs
  src/parser.cxx  
  src/solver.cxx
  src/result.cxx
  src/astar.cxx
  src/global.cxx
  )
target_link_libraries(libs 
  cadgeometry
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)


add_executable(Report app/report.cxx)
  target_link_libraries(Report
  libs
)

add_executable(Draw app/draw.cxx)
target_link_libraries(Draw
  libs
  ${Cairomm_LIBRARIES}
)

add_executable(Solver app/solver.cxx)
target_link_libraries(Solver
  libs
)

  IF(EXISTS "${PROJECT_SOURCE_DIR}/ext-libs/rapidcheck/CMakeLists.txt")
  add_subdirectory("ext-libs/rapidcheck")
  add_subdirectory(test)
ENDIF()
