#include "assertions.hpp"
#include <core/user/user.h>
#include <core/car/car.h>
#include <core/car/car_booking.h>
#include <core/user/user_repository.h>
#include <vector>
#include <array>
#include <list>
#include <console/application.h>

std::vector<char*> parse_argv(const std::string& cmnd)
{
    using namespace std;

    istringstream command_stream(cmnd);
    string s;
    std::vector<char*> opts_car_add;

    while (getline(command_stream, s, ' '))
    {
        char* val = new char[s.size() + 1];
        copy(s.begin(), s.end(), val);
        val[s.size()] = (char)'\0';
        opts_car_add.push_back(val);
    }
    return opts_car_add;
};

const int parse_argc(const std::string& s)
{
    return std::count(s.begin(), s.end(), ' ') + 1;
}

/* UNIT */
void test_create_user()
{
    crs::core::user::user user{"test_name", "sdf"};

    assert_equals(user.get_name(), (std::string)"test_name", __FUNCTION__);
    assert_equals(user.get_role(), crs::core::user::USER_ROLE::CUSTOMER, __FUNCTION__);
}

std::stringstream run_app(const std::string command)
{
    std::stringstream buffer;
    auto argv = parse_argv(command);
    auto app = new crs::console::application(parse_argc(command), &argv[0], buffer);
    app->handle();
    return buffer;
}

/* ACCEPTANCE */
void test_help_when_no_command_expect_see_all_commands_helps()
{
    std::stringstream buffer = run_app("car_rental_system -h");

    assert_has_text(buffer.str(),
        "Car Rental System - help with the rental process, users and cars management",
        __FUNCTION__);
    assert_has_text(buffer.str(), "car_rental_system register", __FUNCTION__);
    assert_has_text(buffer.str(), "car_rental_system car:add", __FUNCTION__);
    assert_has_text(buffer.str(), "car_rental_system register", __FUNCTION__);
}

void test_help_when_register_command_expect_no_other_commands()
{
    std::stringstream buffer = run_app("car_rental_system register -h");

    assert_has_text(buffer.str(),
        "Car Rental System - help with the rental process, users and cars management",
        __FUNCTION__);
    assert_has_text(buffer.str(), "car_rental_system register", __FUNCTION__);
    assert_no_text(buffer.str(), "car_rental_system car:add", __FUNCTION__);
}

void test_help_when_command_not_exist_expect_error()
{
    try
    {
        std::stringstream buffer = run_app("car_rental_system no_such_command -h");
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
    auto buffer = run_app("car_rental_system register -u u -p p -a");

    assert_has_text(buffer.str(), "Admin with username", __FUNCTION__);
    assert_has_text(buffer.str(), "was created", __FUNCTION__);

    auto buffer_car = run_app(
        "car_rental_system car:add -u u -p p --make toyota --model x2 --year 2020 --price-per-day 1"
    );

    assert_has_text(buffer_car.str(), "Car", __FUNCTION__);
    assert_has_text(buffer_car.str(), "added", __FUNCTION__);
}

void add_admin()
{
    auto buffer_car = run_app("car_rental_system register -u a -p p -a");
}

void add_customer()
{
    auto buffer_car = run_app("car_rental_system register -u c -p p");
}

void test_calculate_rent_when_car_available_expect_correct_price()
{
    add_admin();
    // add car
    auto buffer_car = run_app(
        "car_rental_system car:add -u a -p p --make toyota --model x2 --year 2020 --price-per-day 1"
    );

    // see price
    auto buffer_calc = run_app(
        "car_rental_system rent:calculate --start 01/01/2025 --end 10/01/2025 -i 1"
    );
    assert_has_text(buffer_calc.str(), ": 10 NZD", __FUNCTION__);
}

void test_calculate_or_book_when_car_booked_expect_error_when_dates_not_available()
{
    add_admin();
    // add car
    auto buffer_car = run_app(
        "car_rental_system car:add -u a -p p --make toyota --model x2 --year 2020 --price-per-day 1"
    );

    add_customer();
    // book car
    auto buffer_calc = run_app(
        "car_rental_system booking:add --start 01/01/2025 --end 10/01/2025 -i 1 -u c -p p"
    );

    std::list<array<std::string, 2>> unavailable_dates{
        array<std::string, 2>{"01/01/2025", "10/01/2025"},
        array<std::string, 2>{"01/01/2024", "10/01/2026"},
        array<std::string, 2>{"02/01/2025", "09/01/2025"},
        array<std::string, 2>{"09/01/2025", "15/01/2025"},
        array<std::string, 2>{"25/12/2024", "05/01/2025"},
        array<std::string, 2>{"25/12/2024", "01/01/2025"},
        array<std::string, 2>{"10/01/2025", "11/01/2025"},
        array<std::string, 2>{"10/01/2025", "10/01/2025"},
        array<std::string, 2>{"01/01/2025", "01/01/2025"},
        array<std::string, 2>{"04/01/2025", "04/01/2025"},
    };

    // another customer can NOT book those dates
    bool has_expected_exception;

    for (const auto& dates : unavailable_dates)
    {
        has_expected_exception = false;

        try
        {
            auto buffer = run_app(
                "car_rental_system rent:calculate --start " + std::string(dates[0]) +
                    " --end " + std::string(dates[1]) + " -i 1"
            );
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
        has_expected_exception = false;

        try
        {
            auto buffer = run_app(
                "car_rental_system booking:add --start " + std::string(dates[0]) +
                    " --end " + std::string(dates[1]) + " -i 1 -u c -p p"
            );
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
    std::list<array<std::string, 2>> available_dates{
        array<std::string, 2>{"11/01/2025", "11/01/2025"},
        array<std::string, 2>{"31/12/2024", "31/12/2024"},
        array<std::string, 2>{"01/01/2026", "10/01/2026"},
        array<std::string, 2>{"01/01/2024", "10/01/2024"},
    };
    for (const auto& dates : available_dates)
    {
        auto buffer = run_app(
            "car_rental_system rent:calculate --start " + std::string(dates[0]) +
                " --end " + std::string(dates[1]) + " -i 1"
        );

        assert_has_text(buffer.str(), "Total payment will be", __FUNCTION__);
    }
}

void test_book_car_when_car_available_expect_success_booking()
{
    add_admin();
    // add car
    auto buffer_car = run_app(
        "car_rental_system car:add -u a -p p --make toyota --model x2 --year 2020 --price-per-day 10"
    );

    add_customer();
    // see price
    auto buffer_calc = run_app(
        "car_rental_system booking:add --start 01/01/2025 --end 01/01/2025 -i 1 -u c -p p"
    );
    assert_has_text(buffer_calc.str(),
        "Car has successfully been booked, the payment will be 10 NZD",
        __FUNCTION__);
}

void test_car_list_by_customer_when_car_created_by_admin_expect_customer_sees_car()
{
    add_admin();

    std::string make = "toyota";
    std::string model = "x2";
    std::string year = "2020";

    auto buffer_car = run_app(
        "car_rental_system car:add -u a -p p --price-per-day 1"
        " --make " + make + " --model " + model + " --year " + year
    );
    assert_has_text(buffer_car.str(), "Car", __FUNCTION__);
    assert_has_text(buffer_car.str(), "added", __FUNCTION__);

    auto buffer_list = run_app(
        "car_rental_system car:list"
    );

    assert_has_text(buffer_list.str(), "Car List", __FUNCTION__);
    assert_has_text(buffer_list.str(), make, __FUNCTION__);
    assert_has_text(buffer_list.str(), model, __FUNCTION__);
    assert_has_text(buffer_list.str(), year, __FUNCTION__);
}

void test_add_car_when_register_as_customer_expect_failed_to_add()
{
    auto buffer = run_app(
        "car_rental_system register -u u -p p"
    );

    assert_has_text(buffer.str(), "Customer with username", __FUNCTION__);
    assert_has_text(buffer.str(), "was created", __FUNCTION__);

    try
    {
        auto buffer_car = run_app(
            "car_rental_system car:add -u u -p p --make toyota --model x2 --year 2020"
        );
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
    try
    {
        auto buffer = run_app(
            "car_rental_system car:add -u no_such_user -p p"
        );
    }
    catch (const std::exception& exc)
    {
        assert_equals((std::string)"User not found!", (std::string)exc.what(), __FUNCTION__);
        return;
    };
    show_error_msg("Expected an exception but didn't have any", __FUNCTION__);
}

void test_car_add_when_not_existed_user_expect_error2()
{
    try
    {
        auto buffer = run_app(
            "car_rental_system car:add -u no_such_user -p p"
        );
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
        []() -> void { test_car_add_when_not_existed_user_expect_error2(); },
        []() -> void { test_create_user(); },
    };
    for (auto& test : tests)
    {
        try
        {
            clear_db();
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
