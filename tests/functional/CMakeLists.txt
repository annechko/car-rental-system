cmake_minimum_required(VERSION 3.26)
project(car_rental_system_tests)

set(CMAKE_CXX_STANDARD 20)



add_executable(user_tests user.cpp
        ./../../src/core/user/user.h
        ./../../src/core/user/user.cpp
        ./../../src/core/auth/auth_service.h
        ./../../src/core/auth/auth_service.cpp
)
add_executable(car_tests car.cpp)

add_test(
        NAME user_tests
        COMMAND $<TARGET_FILE:user_tests>
)
add_test(
        NAME car_tests
        COMMAND $<TARGET_FILE:car_tests>
)

