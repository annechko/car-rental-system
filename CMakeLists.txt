cmake_minimum_required(VERSION 3.26)
project(car_rental_system)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})

add_executable(car_rental_system main.cpp
        src/core/user/user.h
        src/core/user/user.cpp
        src/core/auth/auth_service.h
        src/core/auth/auth_service.cpp
        src/core/core_exception.h
        src/core/storage/storage.h
        src/core/storage/storage.cpp
        src/core/user/user_repository.h
        src/core/user/user_repository.cpp
        src/console/command/abstract_command.h
        src/console/command/abstract_command.cpp
        src/console/command/sign_up.h
        src/console/command/sign_up.cpp
        src/console/command/login.h
        src/console/command/login.cpp
        src/console/command/user_add.h
        src/console/command/user_add.cpp
        src/console/input_parser.h
        src/console/input_parser.cpp
        src/console/application.h
        src/console/application.cpp
)
set(APP_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(APP_ROOT_SRC_DIR ${APP_ROOT_DIR}/src)
set(SHARED_INCLUDES
        ${APP_ROOT_SRC_DIR}
)
include_directories(${SHARED_INCLUDES})

include(CTest)
enable_testing()
add_subdirectory(tests)

include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/external)
FetchContent_Declare(
        sqlite_orm
        GIT_REPOSITORY https://github.com/fnc12/sqlite_orm.git
        GIT_TAG        master
)

FetchContent_MakeAvailable(sqlite_orm)
target_link_libraries(car_rental_system PRIVATE sqlite_orm)

set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/external)
FetchContent_Declare(
        cxxopts
        GIT_REPOSITORY https://github.com/jarro2783/cxxopts
        GIT_TAG        v3.1.1
)

FetchContent_MakeAvailable(cxxopts)
target_link_libraries(car_rental_system PRIVATE cxxopts)
