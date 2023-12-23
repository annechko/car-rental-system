cmake_minimum_required(VERSION 3.26)
project(car_rental_system_tests)

add_executable(app_tests app.cpp)
target_link_libraries(app_tests PRIVATE app)
target_link_libraries(app_tests PRIVATE tabulate)
target_link_libraries(app_tests PRIVATE bcrypt)
target_link_libraries(app_tests PRIVATE cxxopts)
target_link_libraries(app_tests PRIVATE sqlite_orm)

add_test(
        NAME app_tests
        COMMAND $<TARGET_FILE:app_tests>
)
set_tests_properties(app_tests PROPERTIES
        ENVIRONMENT ENV_TEST=1)
