#include <iostream>
#include <functional>
#include "../src/core/core_exception.h"
#define TESTS_VERBOSE true

static int assertions_count = 0;

void show_error_msg(std::string s, std::string func_name = "")
{
    printf("\x1B[31m");
    std::cout << func_name << ": " << s << "\n";
    printf("\033[0m");
    throw -1;
}

void show_success_msg(std::string s, std::string func_name = "")
{
    printf("\x1B[32m");
    std::cout << (std::string)(func_name == "" ? "" : func_name + ": ") << s << "\n";
    printf("\033[0m");
}

void success_assertion(std::string func_name = "")
{
    assertions_count++;
    if (TESTS_VERBOSE)
    {
        show_success_msg("Assertions is correct.", func_name);
    }
}

template<class SomeType>
void assert_equals(SomeType a, SomeType b, std::string func_name = "")
{
    if (a == b)
    {
        success_assertion(func_name);
        return;
    }
    show_error_msg("Not equals!", func_name);
}

void assert_end()
{
    show_success_msg("All tests passed! " + std::to_string(assertions_count) + " assertions.");
}

const std::exception& assert_exception(std::function<void()> f, std::string func_name = "")
{
    try
    {
        f();
    }
    catch (const std::exception& exception)
    {
        success_assertion(func_name);
        return exception;
    };
    show_error_msg("expected exception but didn't catch any!", func_name);
}
