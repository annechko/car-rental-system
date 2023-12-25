cmake_minimum_required(VERSION 3.26)
project(car_rental_system)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})

add_library(app
        src/core/user/user.h
        src/core/user/user.cpp
        src/core/service/auth_service.h
        src/core/service/auth_service.cpp
        src/core/core_exception.hpp
        src/core/storage/storage.h
        src/core/storage/storage.cpp
        src/core/user/user_repository.h
        src/core/user/user_repository.cpp
        src/console/command/abstract_command.h
        src/console/command/abstract_command.cpp
        src/console/command/sign_up.h
        src/console/command/sign_up.cpp
        src/console/command/car_add.h
        src/console/command/car_add.cpp
        src/console/application.h
        src/console/application.cpp
        src/console/text_helper.hpp
        src/core/car/car.h
        src/core/car/car.cpp
        src/core/car/car_repository.h
        src/core/car/car_repository.cpp
        src/core/service/car_service.h
        src/core/service/car_service.cpp
        src/console/command/car_list.h
        src/console/command/car_list.cpp
        src/console/table_formatter.h
        src/console/table_formatter.cpp
        src/console/command/car_update.h
        src/console/command/car_update.cpp
        src/console/command/car_delete.cpp
        src/console/command/car_delete.h
        src/console/command/rent_calculate.cpp
        src/console/command/rent_calculate.h
        src/core/service/rent_service.cpp
        src/core/service/rent_service.h
        src/core/car/date_ymd.h
        src/core/car/date_ymd.cpp
        src/console/command/booking_add.h
        src/console/command/booking_add.cpp
        src/core/car/car_booking_repository.h
        src/core/car/car_booking_repository.cpp
        src/core/car/car_booking.h
        src/core/car/car_booking.cpp
        src/console/command/booking_list.cpp
        src/console/command/booking_list.h
)

set(APP_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(APP_ROOT_SRC_DIR ${APP_ROOT_DIR}/src)
set(SHARED_INCLUDES
        ${APP_ROOT_SRC_DIR}
)
include_directories(${SHARED_INCLUDES})

add_executable(car_rental_system src/main.cpp)

####### ADDING EXTERNAL DEPENDENCIES #######

include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/external)

FetchContent_Declare(
        sqlite_orm
        GIT_REPOSITORY https://github.com/fnc12/sqlite_orm.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(sqlite_orm)

FetchContent_Declare(
        cxxopts
        GIT_REPOSITORY https://github.com/jarro2783/cxxopts
        GIT_TAG        v3.1.1
)
FetchContent_MakeAvailable(cxxopts)

FetchContent_Declare(
        bcrypt
        GIT_REPOSITORY https://github.com/hilch/Bcrypt.cpp
        GIT_TAG        master
)
FetchContent_MakeAvailable(bcrypt)

FetchContent_Declare(
        tabulate
        GIT_REPOSITORY https://github.com/p-ranav/tabulate
        GIT_TAG master
)
FetchContent_MakeAvailable(tabulate)

target_link_libraries(app PRIVATE bcrypt)
target_link_libraries(app PRIVATE sqlite_orm)
target_link_libraries(app PRIVATE cxxopts)
target_link_libraries(app PRIVATE tabulate)
target_link_libraries(car_rental_system PRIVATE bcrypt)
target_link_libraries(car_rental_system PRIVATE sqlite_orm)
target_link_libraries(car_rental_system PRIVATE cxxopts)
target_link_libraries(car_rental_system PRIVATE tabulate)
target_link_libraries(car_rental_system PRIVATE app)

include(CTest)
enable_testing()
add_subdirectory(tests)
