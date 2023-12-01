cmake_minimum_required(VERSION 3.26)
project(car_rental_system)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})

add_executable(car_rental_system main.cpp
        )

include(CTest)
enable_testing()
add_subdirectory(tests/functional)

#project(car_rental_system_tests)


#if(BUILD_TESTING)
#add_test(simple ${CMAKE_CTEST_COMMAND}
#        --build-and-test "${CMAKE_SOURCE_DIR}/tests/functional"
#        "${CMAKE_BINARY_DIR}/tests/functional"
#        --build-generator ${CMAKE_GENERATOR}
#        --build-makeprogram ${CMAKE_MAKE_PROGRAM}
#        --build-project Simple
#        --test-command simple)
#        add_test(NAME UserTest COMMAND test
#                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests/functional/
#
#        )
#endif()

