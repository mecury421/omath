cmake_minimum_required(VERSION 2.8)
project(ObscureMath CXX)

# Project Options
option(omath_enable_testing "Enable Unit Tests for OMath" OFF)

# Library Target
include_directories("lib")
add_library(omath "lib/U33.cpp")

# Testing
if (omath_enable_testing)

    # Enable testing
    enable_testing()

    # Add test target
    add_executable(test_u33 "test/test_u33.cpp")
    target_link_libraries(test_u33 omath)

    # Add the test case (only one for now)
    add_test(test_u33 test_u33)

    # Add profile target
    add_executable(profile_u33 "test/profile_u33.cpp")
    target_link_libraries(profile_u33 omath)

endif (omath_enable_testing)
