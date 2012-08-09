cmake_minimum_required(VERSION 2.8)
project(BorlandMath CXX)

include_directories("lib")
add_library(bmath "lib/U33.cpp")

add_executable(test_bmath "test.cpp")
target_link_libraries(test_bmath bmath)

add_executable(profile_bmath "profile.cpp")
target_link_libraries(profile_bmath bmath)
