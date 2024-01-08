#include "assertions.hpp"
#include <core/user/user.h>
#include <core/car/car.h>
#include <core/car/car_booking.h>
#include <core/user/user_repository.h>
#include <vector>
#include <array>
#include <list>
#include <console/application.h>

/* UNIT */
void test_create_user()
{
    crs::core::user::user user{ "test_name", "sdf" };

    assert_equals(user.get_name(), (std::string)"test_name", __FUNCTION__);
    assert_equals(user.get_role(), crs::core::user::USER_ROLE::CUSTOMER, __FUNCTION__);
}

/* ACCEPTANCE */
void test_help_when_no_command_expect_see_all_commands_helps()
{
    char* argv_test[] = { (char*)"car_rental_system", (char*)"-h", };
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

void test_help_when_register_command_expect_no_other_commands()
{
    char* argv_test[] = { (char*)"car_rental_system", (char*)"register", (char*)"-h", };
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

void test_help_when_command_not_exist_expect_error()
{
    char* argv_test[] = { (char*)"car_rental_system", (char*)"no_such_command", (char*)"-h", };
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

void test_add_car_when_register_as_admin_expect_car_created()
{
    char* opts_register[]
        { (char*)"car_rental_system", (char*)"register", (char*)"-u", (char*)"u", (char*)"-p", (char*)"p",
          (char*)"-a", };
    std::stringstream buffer;
    (new crs::console::application(7, opts_register, buffer))->handle();

    assert_has_text(buffer.str(), "Admin with username", __FUNCTION__);
    assert_has_text(buffer.str(), "was created", __FUNCTION__);
    char* opts_car_add[]{ (char*)"car_rental_system", "car:add", "-u", "u", "-p", "p",
                          "--make", "toyota",
                          "--model", "x2",
                          "--year", "2020",
    };

    std::stringstream buffer_car;
    (new crs::console::application(12, opts_car_add, buffer_car))->handle();
    assert_has_text(buffer_car.str(), "Car", __FUNCTION__);
    assert_has_text(buffer_car.str(), "added", __FUNCTION__);
}

void add_admin()
{
    char* opts_register[]
        { (char*)"car_rental_system", (char*)"register",
          (char*)"-u", (char*)"a", (char*)"-p", (char*)"p", (char*)"-a", };
    std::stringstream buffer;
    (new crs::console::application(7, opts_register, buffer))->handle();
}

void add_customer()
{
    char* opts_register[]
        { (char*)"car_rental_system", (char*)"register",
          (char*)"-u", (char*)"c", (char*)"-p", (char*)"p" };
    std::stringstream buffer;
    (new crs::console::application(6, opts_register, buffer))->handle();
}

void test_calculate_rent_when_car_available_expect_correct_price()
{
    add_admin();
    // add car
    char* opts_car_add[]{ (char*)"car_rental_system", "car:add", "-u", "a", "-p", "p",
                          "--make", "toyota",
                          "--model", "x2",
                          "--year", "2020",
                          "--price-per-day", "1"
    };

    std::stringstream buffer_car;
    (new crs::console::application(14, opts_car_add, buffer_car))->handle();
    // see price
    char* opts_calculate[]{ (char*)"car_rental_system", "rent:calculate",
                            "--start", "01/01/2025",
                            "--end", "10/01/2025",
                            "-i", "1"
    };

    std::stringstream buffer_calc;
    (new crs::console::application(8, opts_calculate, buffer_calc))->handle();
    assert_has_text(buffer_calc.str(), ": 10 NZD", __FUNCTION__);
}

void test_calculate_or_book_when_car_booked_expect_error_when_dates_not_available()
{
    add_admin();
    // add car
    char* opts_car_add[]{ (char*)"car_rental_system", "car:add", "-u", "a", "-p", "p",
                          "--make", "toyota",
                          "--model", "x2",
                          "--year", "2020",
                          "--price-per-day", "1"
    };
    std::stringstream buffer_car;
    (new crs::console::application(14, opts_car_add, buffer_car))->handle();

    add_customer();
    char* opts_calculate[]{ (char*)"car_rental_system", "booking:add",
                            "--start", "01/01/2025",
                            "--end", "10/01/2025",
                            "-i", "1",
                            "-u", "c", "-p", "p",
    };
    std::stringstream buffer_calc;
    (new crs::console::application(12, opts_calculate, buffer_calc))->handle();

    std::list<array<char*, 2>> unavailable_dates{
        array<char*, 2>{ "01/01/2025", "10/01/2025" },
        array<char*, 2>{ "01/01/2024", "10/01/2026" },
        array<char*, 2>{ "02/01/2025", "09/01/2025" },
        array<char*, 2>{ "09/01/2025", "15/01/2025" },
        array<char*, 2>{ "25/12/2024", "05/01/2025" },
        array<char*, 2>{ "25/12/2024", "01/01/2025" },
        array<char*, 2>{ "10/01/2025", "11/01/2025" },
        array<char*, 2>{ "10/01/2025", "10/01/2025" },
        array<char*, 2>{ "01/01/2025", "01/01/2025" },
        array<char*, 2>{ "04/01/2025", "04/01/2025" },
    };

    // another customer can NOT book those dates
    bool has_expected_exception;
    std::stringstream buffer;

    for (const auto& dates : unavailable_dates)
    {
        char* opts_calculate[]{ (char*)"car_rental_system", "rent:calculate",
                                "--start", dates[0],
                                "--end", dates[1],
                                "-i", "1"
        };
        has_expected_exception = false;
        buffer.clear();
        buffer.str(std::string());

        try
        {
            (new crs::console::application(8, opts_calculate, buffer))->handle();
        }
        catch (const std::exception& e)
        {
            has_expected_exception = true;
            assert_has_text(e.what(), "unavailable", __FUNCTION__);
        }
        if (has_expected_exception == false)
        {
            show_error_msg(
                "dates " + std::string(dates[0]) + " - " + dates[1] + " should be unavailable.",
                __FUNCTION__);
        }
    }
    for (const auto& dates : unavailable_dates)
    {
        char* opts_calculate[]{ (char*)"car_rental_system", "booking:add",
                                "--start", dates[0],
                                "--end", dates[1],
                                "-i", "1", "-u", "c", "-p", "p",

        };
        has_expected_exception = false;
        buffer.clear();
        buffer.str(std::string());

        try
        {
            (new crs::console::application(12, opts_calculate, buffer))->handle();
        }
        catch (const std::exception& e)
        {
            has_expected_exception = true;
            assert_has_text(e.what(), "unavailable", __FUNCTION__);
        }
        if (has_expected_exception == false)
        {
            show_error_msg(
                "dates " + std::string(dates[0]) + " - " + dates[1] + " should be unavailable.",
                __FUNCTION__);
        }
    }

    // but CAN book those dates
    std::list<array<char*, 2>> available_dates{
        array<char*, 2>{ "11/01/2025", "11/01/2025" },
        array<char*, 2>{ "31/12/2024", "31/12/2024" },
        array<char*, 2>{ "01/01/2026", "10/01/2026" },
        array<char*, 2>{ "01/01/2024", "10/01/2024" },
    };
    for (const auto& dates : available_dates)
    {
        char* opts_calculate[]{ (char*)"car_rental_system", "rent:calculate",
                                "--start", dates[0],
                                "--end", dates[1],
                                "-i", "1"
        };
        buffer.clear();
        buffer.str(std::string());

        (new crs::console::application(8, opts_calculate, buffer))->handle();

        assert_has_text(buffer.str(), "Total payment will be", __FUNCTION__);
    }
}

void test_book_car_when_car_available_expect_success_booking()
{
    add_admin();
    // add car
    char* opts_car_add[]{ (char*)"car_rental_system", "car:add", "-u", "a", "-p", "p",
                          "--make", "toyota",
                          "--model", "x2",
                          "--year", "2020",
                          "--price-per-day", "10"
    };

    std::stringstream buffer_car;
    (new crs::console::application(14, opts_car_add, buffer_car))->handle();

    add_customer();
    // see price
    char* opts_calculate[]{ (char*)"car_rental_system", "booking:add",
                            "--start", "01/01/2025",
                            "--end", "01/01/2025",
                            "-i", "1",
                            "-u", "c",
                            "-p", "p"
    };

    std::stringstream buffer_calc;
    (new crs::console::application(12, opts_calculate, buffer_calc))->handle();
    assert_has_text(buffer_calc.str(),
        "Car has successfully been booked, the payment will be 10 NZD",
        __FUNCTION__);
}

void test_car_list_by_customer_when_car_created_by_admin_expect_customer_sees_car()
{
    char* opts_register[]{ (char*)"car_rental_system", "register", "-u", "u", "-p", "p", "-a", };
    std::stringstream buffer;
    (new crs::console::application(7, opts_register, buffer))->handle();

    assert_has_text(buffer.str(), "Admin with username", __FUNCTION__);
    assert_has_text(buffer.str(), "was created", __FUNCTION__);
    char* make = "toyota";
    char* model = "x2";
    char* year = "2020";
    char* opts_car_add[]{ (char*)"car_rental_system", "car:add", "-u", "u", "-p", "p",
                          "--make", make,
                          "--model", model,
                          "--year", year,
    };

    std::stringstream buffer_car;
    (new crs::console::application(12, opts_car_add, buffer_car))->handle();
    assert_has_text(buffer_car.str(), "Car", __FUNCTION__);
    assert_has_text(buffer_car.str(), "added", __FUNCTION__);

    char* opts_car_list[]{ (char*)"car_rental_system", "car:list", };
    std::stringstream buffer_list;
    (new crs::console::application(2, opts_car_list, buffer_list))->handle();

    assert_has_text(buffer_list.str(), "Car List", __FUNCTION__);
    assert_has_text(buffer_list.str(), make, __FUNCTION__);
    assert_has_text(buffer_list.str(), model, __FUNCTION__);
    assert_has_text(buffer_list.str(), year, __FUNCTION__);
}

void test_add_car_when_register_as_customer_expect_failed_to_add()
{
    char* opts_register[]{ (char*)"car_rental_system", "register", "-u", "u", "-p", "p", };
    std::stringstream buffer;
    (new crs::console::application(6, opts_register, buffer))->handle();

    assert_has_text(buffer.str(), "User with username", __FUNCTION__);
    assert_has_text(buffer.str(), "was created", __FUNCTION__);
    char* opts_car_add[]{ (char*)"car_rental_system", "car:add", "-u", "u", "-p", "p",
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

void test_car_add_when_not_existed_user_expect_error()
{
    char* opts_car_add[]{ (char*)"car_rental_system", "car:add", "-u", "no_such_user", "-p", "p" };

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
    db->remove_all<crs::core::car::car_booking>();
}

int main()
{
    int res = 0;
    std::vector<std::function<void()>> tests{
        []() -> void { test_help_when_no_command_expect_see_all_commands_helps(); },
        []() -> void { test_help_when_register_command_expect_no_other_commands(); },
        []() -> void { test_help_when_command_not_exist_expect_error(); },
        []() -> void { test_add_car_when_register_as_admin_expect_car_created(); },
        []() -> void { test_car_list_by_customer_when_car_created_by_admin_expect_customer_sees_car(); },
        []() -> void { test_calculate_rent_when_car_available_expect_correct_price(); },
        []() -> void { test_calculate_or_book_when_car_booked_expect_error_when_dates_not_available(); },
        []() -> void { test_book_car_when_car_available_expect_success_booking(); },
        []() -> void { test_add_car_when_register_as_customer_expect_failed_to_add(); },
        []() -> void { test_car_add_when_not_existed_user_expect_error(); },
        []() -> void { test_create_user(); },
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
