cmake_minimum_required(VERSION 3.26)
project(car_rental_system VERSION 0.1 LANGUAGES CXX)

##### Project wide setup ####
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})


add_executable(car_rental_system src/main.cpp)
####### ADDING EXTERNAL DEPENDENCIES #######

include(FetchContent)
#set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/external)

FetchContent_Declare(
        sqlite_orm
        GIT_REPOSITORY https://github.com/fnc12/sqlite_orm.git
        GIT_TAG v1.8.2
)
FetchContent_MakeAvailable(sqlite_orm)

target_link_libraries(car_rental_system PRIVATE sqlite_orm::sqlite_orm)

