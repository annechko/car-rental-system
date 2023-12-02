#include "../assertions.hpp"
#include "../../src/core/user/user.h"
#include "../../src/core/auth/auth_service.h"
#include <vector>

void testLogin()
{
    crs::core::auth::auth_service service{};
    crs::core::user::user user = service.login("test_user", "test_pass");
	assertEquals(user.get_name(), (std::string)"test_user", __FUNCTION__);
	assertEquals(user.get_role(), crs::core::user::ROLE::CUSTOMER, __FUNCTION__);
}

void testRegister()
{
	assertEquals(1, 1, __FUNCTION__);
}

int main()
{
	int res = 0;
	std::vector<std::function<void()>> tests{
		[]() -> void
		{ testLogin(); },
		[]() -> void
		{ testRegister(); },
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

	return res;
}
