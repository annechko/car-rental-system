#define TESTS_VERBOSE true
#include <iostream>
#include <functional>
#include "../src/core/core_exception.hpp"
#include <type_traits>

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

template<class some_type>
void assert_equals(some_type a, some_type b, std::string func_name = "")
{
    if (a == b)
    {
        success_assertion(func_name);
        return;
    }
    if constexpr (std::is_same<some_type, std::string>::value)
    {
        show_error_msg(
            "Failed asserting that \"" + (std::string)a + "\" is equal to \"" + (std::string)b + "\"",
            func_name
        );
    }
    else
    {
        show_error_msg("Not equals!", func_name);
    }
}

void assert_has_text(std::string haystack, std::string needle, std::string func_name = "")
{
    if (std::string::npos != haystack.find(needle))
    {
        success_assertion(func_name);
        return;
    }
    show_error_msg("Failed asserting that \"" + needle + "\" was in \"" + haystack + "\"", func_name);
}

void assert_no_text(std::string haystack, std::string needle, std::string func_name = "")
{
    if (std::string::npos == haystack.find(needle))
    {
        success_assertion(func_name);
        return;
    }
    show_error_msg("Not found " + needle + " in " + haystack, func_name);
}

void assert_end()
{
    show_success_msg("All tests passed! " + std::to_string(assertions_count) + " assertions.");
}
