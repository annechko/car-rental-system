#include "assertions.hpp"
#include <core/user/user.h>
#include <core/car/car.h>
#include <core/user/user_repository.h>
#include <vector>
#include <console/application.h>

/* UNIT */
void testCreateUser()
{
    crs::core::user::user user{ "test_name", "sdf" };

    assert_equals(user.get_name(), (std::string)"test_name", __FUNCTION__);
    assert_equals(user.get_role(), crs::core::user::USER_ROLE::CUSTOMER, __FUNCTION__);
}

/* ACCEPTANCE */
void testHelp_NoCommand_SeeAllCommandsHelps()
{
    char* argv_test[] = { "car_rental_system", "-h", };
    int argc_test = 2;
    std::stringstream buffer;
    auto app = new crs::console::application(argc_test, argv_test, buffer);
    app->handle();

    assert_has_text(buffer.str(),
        "Car Rental System - help with the rental process, users and cars management",
        __FUNCTION__);
    assert_has_text(buffer.str(), "car_rental_system register", __FUNCTION__);
    assert_has_text(buffer.str(), "car_rental_system car:add", __FUNCTION__);
    assert_has_text(buffer.str(), "car_rental_system register", __FUNCTION__);
}

void testHelp_ForRegisterCommand_dontSeeOtherCommands()
{
    char* argv_test[] = { "car_rental_system", "register", "-h", };
    int argc_test = 3;
    std::stringstream buffer;
    auto app = new crs::console::application(argc_test, argv_test, buffer);
    app->handle();

    assert_has_text(buffer.str(),
        "Car Rental System - help with the rental process, users and cars management",
        __FUNCTION__);
    assert_has_text(buffer.str(), "car_rental_system register", __FUNCTION__);
    assert_no_text(buffer.str(), "car_rental_system car:add", __FUNCTION__);
}

void testHelp_CommandNotExist_Error()
{
    char* argv_test[] = { "car_rental_system", "no_such_command", "-h", };
    int argc_test = 3;
    std::stringstream buffer;
    auto app = new crs::console::application(argc_test, argv_test, buffer);
    try
    {
        app->handle();
    }
    catch (std::exception& exc)
    {
        assert_equals((std::string)"Command \"no_such_command\" does not exist!",
            (std::string)exc.what(),
            __FUNCTION__);
        return;
    };
    show_error_msg("Expected an exception but didn't have any");
}

void testRegisterAsAdmin_AddCar_CarCreated()
{
    char* opts_register[]{ "car_rental_system", "register", "-u", "u", "-p", "p", "-a", };
    std::stringstream buffer;
    (new crs::console::application(7, opts_register, buffer))->handle();

    assert_has_text(buffer.str(), "User with username", __FUNCTION__);
    assert_has_text(buffer.str(), "was created", __FUNCTION__);
    char* opts_car_add[]{ "car_rental_system", "car:add", "-u", "u", "-p", "p",
                          "--make", "toyota",
                          "--model", "x2",
                          "--year", "2020",
    };

    std::stringstream buffer_car;
    (new crs::console::application(12, opts_car_add, buffer_car))->handle();
    assert_has_text(buffer_car.str(), "Car", __FUNCTION__);
    assert_has_text(buffer_car.str(), "added", __FUNCTION__);
}

void testRegisterAsCustomer_AddCar_FailedToAdd()
{
    char* opts_register[]{ "car_rental_system", "register", "-u", "u", "-p", "p", };
    std::stringstream buffer;
    (new crs::console::application(6, opts_register, buffer))->handle();

    assert_has_text(buffer.str(), "User with username", __FUNCTION__);
    assert_has_text(buffer.str(), "was created", __FUNCTION__);
    char* opts_car_add[]{ "car_rental_system", "car:add", "-u", "u", "-p", "p",
                          "--make", "toyota",
                          "--model", "x2",
                          "--year", "2020",
    };

    std::stringstream buffer_car;
    try
    {
        (new crs::console::application(12, opts_car_add, buffer_car))->handle();
    }
    catch (const std::exception& exc)
    {
        assert_has_text(
            (std::string)exc.what(),
            (std::string)"This command can be run only by admin user",
            __FUNCTION__
        );
        return;
    };
    show_error_msg("Expected an exception but didn't catch any", __FUNCTION__);
}

void testCarAdd_ByNotExistedUser_SeeError()
{
    char* opts_car_add[]{ "car_rental_system", "car:add", "-u", "no_such_user", "-p", "p" };

    std::stringstream buffer;
    auto app = new crs::console::application(6, opts_car_add, buffer);
    try
    {
        app->handle();
    }
    catch (const std::exception& exc)
    {
        assert_equals((std::string)"User not found!", (std::string)exc.what(), __FUNCTION__);
        return;
    };
    show_error_msg("Expected an exception but didn't have any", __FUNCTION__);
}

void clear_db()
{
    auto db = crs::core::storage::storage::get_instance()->get_db();
    db->remove_all<crs::core::user::user>();
    db->remove_all<crs::core::car::car>();
}

int main()
{
    int res = 0;
    std::vector<std::function<void()>> tests{
        []() -> void { testHelp_NoCommand_SeeAllCommandsHelps(); },
        []() -> void { testHelp_ForRegisterCommand_dontSeeOtherCommands(); },
        []() -> void { testHelp_CommandNotExist_Error(); },
        []() -> void { testRegisterAsAdmin_AddCar_CarCreated(); },
        []() -> void { testRegisterAsCustomer_AddCar_FailedToAdd(); },
        []() -> void { testCarAdd_ByNotExistedUser_SeeError(); },
        []() -> void { testCreateUser(); },
    };
    for (auto& test : tests)
    {
        clear_db();
        try
        {
            test();
        }
        catch (const std::exception& exception)
        {
            res = 1;
            show_error_msg(exception.what(), __FUNCTION__);
        }
    }

    if (res == 0)
    {
        assert_end();
    }
    return res;
}
