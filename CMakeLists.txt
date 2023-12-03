cmake_minimum_required(VERSION 3.26)
project(car_rental_system)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})

add_executable(car_rental_system main.cpp
        src/core/user/user.h
        src/core/user/user.cpp
        src/core/auth/auth_service.h
        src/core/auth/auth_service.cpp
)

include(CTest)
enable_testing()
add_subdirectory(tests)
