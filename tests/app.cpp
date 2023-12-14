#include "assertions.hpp"
#include <core/user/user.h>
#include <core/user/user_repository.h>
#include <core/service/auth_service.h>
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
void testHelp_App()
{
    std::string a1 = "car_rental_system";
    std::string a2 = "-h";
    char* argv_test[] = { &a1[0], &a2[0], };
    int argc_test = 2;
    std::stringstream buffer;
    auto app = new crs::console::application(argc_test, argv_test, buffer);
    app->handle();

    assert_has_text(buffer.str(), "Car Rental System - help with the rental process, users and cars management", __FUNCTION__);
    assert_has_text(buffer.str(), "car_rental_system user:add", __FUNCTION__);
    assert_has_text(buffer.str(), "car_rental_system login", __FUNCTION__);
    assert_has_text(buffer.str(), "car_rental_system register", __FUNCTION__);
}

void testHelp_UserAdd()
{
    std::string a1 = "car_rental_system";
    std::string a2 = "user:add";
    std::string a3 = "-h";
    char* argv_test[] = { &a1[0], &a2[0], &a3[0], };
    int argc_test = 3;
    std::stringstream buffer;
    auto app = new crs::console::application(argc_test, argv_test, buffer);
    app->handle();

    assert_has_text(buffer.str(), "Car Rental System - help with the rental process, users and cars management", __FUNCTION__);
    assert_has_text(buffer.str(), "car_rental_system user:add", __FUNCTION__);
    assert_no_text(buffer.str(), "car_rental_system login", __FUNCTION__);
    assert_no_text(buffer.str(), "car_rental_system register", __FUNCTION__);
}

void testHelp_CommandNotExist_Error()
{
    std::string a1 = "car_rental_system";
    std::string a2 = "no_such_command";
    std::string a3 = "-h";
    char* argv_test[] = { &a1[0], &a2[0], &a3[0], };
    int argc_test = 3;
    std::stringstream buffer;
    auto app = new crs::console::application(argc_test, argv_test, buffer);
    try
    {
        app->handle();
    }
    catch (std::exception& exc)
    {
        assert_equals((std::string)"Command \"no_such_command\" does not exist!", (std::string)exc.what(), __FUNCTION__);
        return;
    };
    show_error_msg("Expected an exception but didn't have any");
}

void testLogin_UserOptionNoPassOption_Error()
{
    std::string a1 = "car_rental_system";
    std::string a2 = "login";
    std::string a3 = "-n";
    std::string a4 = "nonono";
    char* argv_test[] = { &a1[0], &a2[0], &a3[0], &a4[0], };
    int argc_test = 4;
    std::stringstream buffer;
    auto app = new crs::console::application(argc_test, argv_test, buffer);
    try
    {
        app->handle();
    }
    catch (std::exception& exc)
    {
        assert_equals((std::string)"Option ‘password’ has no value", (std::string)exc.what(), __FUNCTION__);
        return;
    };
    show_error_msg("Expected an exception but didn't have any");
}

void testLogin_UserNotExist_Error()
{
    std::string a1 = "car_rental_system";
    std::string a2 = "login";
    std::string a3 = "-n";
    std::string a4 = "nono";
    std::string a5 = "-p";
    std::string a6 = "p";
    char* argv_test[] = { &a1[0], &a2[0], &a3[0], &a4[0], &a5[0], &a6[0], };
    int argc_test = 6;
    std::stringstream buffer;
    auto app = new crs::console::application(argc_test, argv_test, buffer);
    try
    {
        app->handle();
    }
    catch (std::exception& exc)
    {
        assert_equals((std::string)"User not found!", (std::string)exc.what(), __FUNCTION__);
        return;
    };
    show_error_msg("Expected an exception but didn't have any", __FUNCTION__);
}

void testRegisterAndLogin()
{
    std::string a1 = "car_rental_system";
    std::string a2 = "user:add";
    std::string a2_login = "login";
    std::string a3 = "-n";
    std::string a4 = "user68kkdfsddfsjkok";
    std::string a5 = "-p";
    std::string a6 = "pass";
    char* argv_test_reg[] = { &a1[0], &a2[0], &a3[0], &a4[0], &a5[0], &a6[0], };
    char* argv_test_login[] = { &a1[0], &a2_login[0], &a3[0], &a4[0], &a5[0], &a6[0], };
    int argc_test = 6;
    std::stringstream buffer;
    auto app = new crs::console::application(argc_test, argv_test_reg, buffer);
    try
    {
        app->handle();
    }
    catch (std::exception& exception)
    {
        assert_equals((std::string)"", (std::string)exception.what(), __FUNCTION__);
    };

    auto app7 = new crs::console::application(argc_test, argv_test_login, buffer);
    try
    {
        app7->handle();
    }
    catch (std::exception& exception)
    {
        assert_equals((std::string)"", (std::string)exception.what(), __FUNCTION__);
    };
}

int main()
{
    int res = 0;
    std::vector<std::function<void()>> tests{
        []() -> void { testHelp_App(); },
        []() -> void { testHelp_UserAdd(); },
        []() -> void { testHelp_CommandNotExist_Error(); },
        []() -> void { testLogin_UserOptionNoPassOption_Error(); },
        []() -> void { testLogin_UserNotExist_Error(); },
        []() -> void { testRegisterAndLogin(); },
        []() -> void { testCreateUser(); },
    };
    for (auto& test : tests)
    {
        try
        {
            test();
        }
        catch (...)
        {
            res = 1;
        }
    }

    if (res == 0)
    {
        assert_end();
    }
    return res;
}
