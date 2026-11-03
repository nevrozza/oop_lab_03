cmake_minimum_required(VERSION 4.1)
project(lab_03)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab_03
    main.cpp
    student/student.cpp
    student/student_set.cpp
    student/student.h
    student/student_set.h
)

include(CTest)
if(BUILD_TESTING)
    find_package(GTest CONFIG QUIET)
    if(NOT TARGET GTest::gtest_main)
        include(FetchContent)
        if(POLICY CMP0135)
            cmake_policy(SET CMP0135 NEW)
        endif()
        set(INSTALL_GTEST OFF)
        FetchContent_Declare(googletest
            URL https://codeload.github.com/google/googletest/tar.gz/refs/tags/v1.15.2
            URL_HASH SHA256=7b42b4d6ed48810c5362c265a17faebe90dc2373c885e5216439d37927f02926
        )
        FetchContent_MakeAvailable(googletest)
    endif()

    add_executable(lab_03_tests tests.cpp student/student.cpp student/student_set.cpp)
    target_link_libraries(lab_03_tests PRIVATE GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(lab_03_tests)
endif()
