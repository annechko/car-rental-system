cmake_minimum_required(VERSION 3.26)
project(car_rental_system_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})
set(APP_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(APP_ROOT_SRC_DIR ${APP_ROOT_DIR}/src)
set(SHARED_INCLUDES
        ${APP_ROOT_SRC_DIR}
)
include_directories(${SHARED_INCLUDES})

add_executable(user_tests user.cpp
        ../src/core/user/user.h
        ../src/core/user/user.cpp
        ../src/core/service/auth_service.h
        ../src/core/service/auth_service.cpp
        ../src/core/storage/storage.h
        ../src/core/storage/storage.cpp
        ../src/core/user/user_repository.h
        ../src/core/user/user_repository.cpp
)
add_executable(car_tests car.cpp)
include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/external)
FetchContent_Declare(
        sqlite_orm
        GIT_REPOSITORY https://github.com/fnc12/sqlite_orm.git
        GIT_TAG        master
)

FetchContent_MakeAvailable(sqlite_orm)
target_link_libraries(user_tests PRIVATE sqlite_orm)


add_test(
        NAME user_tests
        COMMAND $<TARGET_FILE:user_tests>
)
add_test(
        NAME car_tests
        COMMAND $<TARGET_FILE:car_tests>
)
