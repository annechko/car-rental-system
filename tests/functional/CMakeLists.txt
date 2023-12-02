cmake_minimum_required(VERSION 3.26)
project(car_rental_system_tests)

set(CMAKE_CXX_STANDARD 20)

add_executable(user_tests user.cpp)
add_executable(car_tests car.cpp)

add_test(
        NAME user_tests
        COMMAND $<TARGET_FILE:user_tests>
)
add_test(
        NAME car_tests
        COMMAND $<TARGET_FILE:car_tests>
)

