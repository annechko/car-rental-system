cmake_minimum_required(VERSION 3.26)
project(car_rental_system_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})

# testing binary
add_executable(user_tests user.cpp)
add_executable(car_tests car.cpp)
#target_link_libraries(user_tests PRIVATE run)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME user_tests
        COMMAND ${CMAKE_CTEST_COMMAND}
        --build-and-test "${CMAKE_SOURCE_DIR}/tests/functional"
        "${CMAKE_BINARY_DIR}/bin/tests/functional"
        --build-generator ${CMAKE_GENERATOR}
        --build-makeprogram ${CMAKE_MAKE_PROGRAM}
)

add_test(
        NAME car_tests
        COMMAND ${CMAKE_CTEST_COMMAND}
        --build-and-test "${CMAKE_SOURCE_DIR}/tests/functional"
        "${CMAKE_BINARY_DIR}/bin/tests/functional"
        --build-generator ${CMAKE_GENERATOR}
        --build-makeprogram ${CMAKE_MAKE_PROGRAM}
)

