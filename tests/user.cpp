#include "assertions.hpp"
#include "../src/core/user/user.h"
#include "../src/core/auth/auth_service.h"
#include <vector>

/* UNIT */
void testCreateUser()
{
    crs::core::user::user user("test_name");

    assertEquals(user.get_name(), (std::string)"test_name", __FUNCTION__);
    assertEquals(user.get_role(), crs::core::user::ROLE::CUSTOMER, __FUNCTION__);
}

/* FUNCTIONAL */
void testLogin()
{
    crs::core::auth::auth_service service{};
    crs::core::user::user user = service.login("test_user", "test_pass");

    assertEquals(user.get_name(), (std::string)"test_user", __FUNCTION__);
    assertEquals(user.get_role(), crs::core::user::ROLE::CUSTOMER, __FUNCTION__);
}

void testRegister_InvalidName_Exception()
{
    crs::core::auth::auth_service service{};

    const std::exception& exc = assertException([& service]() -> void { service.sign_up("test user", "test_pass"); }, __FUNCTION__);
    assertEquals((std::string)exc.what(), (std::string)"Username is invalid.", __FUNCTION__);
}

void testRegister()
{
    crs::core::auth::auth_service service{};
    crs::core::user::user user = service.sign_up("test_user", "test_pass");

    assertEquals(user.get_name(), (std::string)"test_user", __FUNCTION__);
    assertEquals(user.get_role(), crs::core::user::ROLE::CUSTOMER, __FUNCTION__);
}

int main()
{
    int res = 0;
    std::vector<std::function<void()>> tests{
        []() -> void { testLogin(); },
        []() -> void { testRegister(); },
        []() -> void { testCreateUser(); },
        []() -> void { testRegister_InvalidName_Exception(); },
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
        assertEnd();
    }
    return res;
}
