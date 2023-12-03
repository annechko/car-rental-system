#include "assertions.hpp"
#include <core/user/user_repository.h>
#include <core/auth/auth_service.h>
#include <vector>

/* UNIT */
void testCreateUser()
{
    crs::core::user::user user("test_name");

    assert_equals(user.get_name(), (std::string)"test_name", __FUNCTION__);
    assert_equals(user.get_role(), crs::core::user::ROLE::CUSTOMER, __FUNCTION__);
}

/* FUNCTIONAL */
void testLogin()
{
    crs::core::auth::auth_service service{};
    crs::core::user::user user = service.login("test_user", "test_pass");

    assert_equals(user.get_name(), (std::string)"test_user", __FUNCTION__);
    assert_equals(user.get_role(), crs::core::user::ROLE::CUSTOMER, __FUNCTION__);
}

void testRegister_InvalidName_Exception()
{
    crs::core::auth::auth_service service{};

    const std::exception& exc = assert_exception([& service]() -> void { service.sign_up("test user", "test_pass"); }, __FUNCTION__);
    assert_equals((std::string)exc.what(), (std::string)"Username is invalid.", __FUNCTION__);
}
void testFindUserById_NotExist_Exception()
{
    crs::core::user::user_repository repo;

    const std::exception& exc = assert_exception([& repo]() -> void { repo.get_by_id(42); }, __FUNCTION__);
}

void testRegister()
{
    crs::core::auth::auth_service service{};
    crs::core::user::user user = service.sign_up("test_user", "test_pass");

    assert_equals(user.get_name(), (std::string)"test_user", __FUNCTION__);
    assert_equals(user.get_role(), crs::core::user::ROLE::CUSTOMER, __FUNCTION__);
}

int main()
{
    int res = 0;
    std::vector<std::function<void()>> tests{
        []() -> void { testLogin(); },
        []() -> void { testRegister(); },
        []() -> void { testCreateUser(); },
        []() -> void { testRegister_InvalidName_Exception(); },
        []() -> void { testFindUserById_NotExist_Exception(); },
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
