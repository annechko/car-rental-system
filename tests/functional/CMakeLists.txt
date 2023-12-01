cmake_minimum_required(VERSION 3.26)
project(car_rental_system_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})

add_executable(car_rental_system_tests tests.cpp
        )

enable_testing()

add_test(user ${CMAKE_CTEST_COMMAND}
        --build-and-test "${CMAKE_SOURCE_DIR}/tests/functional"
        "${CMAKE_BINARY_DIR}/bin/tests/functional"
        --build-generator ${CMAKE_GENERATOR}
        --build-makeprogram ${CMAKE_MAKE_PROGRAM}
        --build-project car_rental_system_tests
        --test-command car_rental_system_tests
)

