cmake_minimum_required(VERSION 3.26)
project(car_rental_system)
find_package(SQLite3 REQUIRED)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})


add_executable(car_rental_system src/main.cpp)

####### ADDING EXTERNAL DEPENDENCIES #######

include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/external)

FetchContent_Declare(
        sqlite_orm
        GIT_REPOSITORY https://github.com/fnc12/sqlite_orm.git
        GIT_TAG v1.8.2
)
FetchContent_MakeAvailable(sqlite_orm)

target_link_libraries(car_rental_system PRIVATE sqlite_orm)

