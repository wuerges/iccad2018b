add_executable(TestParse test_parse.cxx)
target_link_libraries(TestParse
    libs
    rapidcheck
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

