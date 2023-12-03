#include <iostream>
#include <functional>
#include "../src/core/validation_exception.h"
#define TESTS_VERBOSE true

static int assertionsCount = 0;

void showErrorMsg(std::string s, std::string funcName = "")
{
    printf("\x1B[31m");
    std::cout << funcName << ": " << s << "\n";
    printf("\033[0m");
    throw -1;
}

void showSuccessMsg(std::string s, std::string funcName = "")
{
    printf("\x1B[32m");
    std::cout << (std::string)(funcName == "" ? "" : funcName + ": ") << s << "\n";
    printf("\033[0m");
}

void successAssertion(std::string funcName = "")
{
    assertionsCount++;
    if (TESTS_VERBOSE)
    {
        showSuccessMsg("Assertions is correct.", funcName);
    }
}

template<class SomeType>
void assertEquals(SomeType a, SomeType b, std::string funcName = "")
{
    if (a == b)
    {
        successAssertion(funcName);
        return;
    }
    showErrorMsg("Not equals!", funcName);
}

void assertEnd()
{
    showSuccessMsg("All tests passed! " + std::to_string(assertionsCount) + " assertions.");
}

const std::exception& assertException(std::function<void()> f, std::string funcName = "")
{
    try
    {
        f();
    }
    catch (const std::exception& exception)
    {
        successAssertion(funcName);
        return exception;
    };
    showErrorMsg("expected exception but didn't catch any!", funcName);
}
