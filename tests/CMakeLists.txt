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

add_executable(app_tests app.cpp
        ../src/core/user/user.h
        ../src/core/user/user.cpp
        ../src/core/service/auth_service.h
        ../src/core/service/auth_service.cpp
        ../src/core/core_exception.h
        ../src/core/storage/storage.h
        ../src/core/storage/storage.cpp
        ../src/core/user/user_repository.h
        ../src/core/user/user_repository.cpp
        ../src/console/command/abstract_command.h
        ../src/console/command/abstract_command.cpp
        ../src/console/command/sign_up.h
        ../src/console/command/sign_up.cpp
        ../src/console/command/login.h
        ../src/console/command/login.cpp
        ../src/console/command/user_add.h
        ../src/console/command/user_add.cpp
        ../src/console/application.h
        ../src/console/application.cpp
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
target_link_libraries(app_tests PRIVATE sqlite_orm)

FetchContent_Declare(
        cxxopts
        GIT_REPOSITORY https://github.com/jarro2783/cxxopts
        GIT_TAG v3.1.1
)

FetchContent_MakeAvailable(cxxopts)
target_link_libraries(app_tests PRIVATE cxxopts)

FetchContent_Declare(
        bcrypt
        GIT_REPOSITORY https://github.com/hilch/Bcrypt.cpp
        GIT_TAG master
)

FetchContent_MakeAvailable(bcrypt)
target_link_libraries(app_tests PRIVATE bcrypt)


add_test(
        NAME app_tests
        COMMAND $<TARGET_FILE:app_tests>
)
add_test(
        NAME car_tests
        COMMAND $<TARGET_FILE:car_tests>
)
