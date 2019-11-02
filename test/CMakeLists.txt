add_executable(TestParse test_parse.cxx)
target_link_libraries(TestParse
    libs
    rapidcheck
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  )


add_executable(TestRTree test_rtree.cxx)
target_link_libraries(TestRTree
    libs
    rapidcheck
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  )
