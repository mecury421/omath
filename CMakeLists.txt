cmake_minimum_required(VERSION 2.8)
project(ObscureMath CXX)

include_directories("lib")
add_library(omath "lib/U33.cpp")

add_executable(test_omath "test.cpp")
target_link_libraries(test_omath omath)

add_executable(profile_omath "profile.cpp")
target_link_libraries(profile_omath omath)
