#include <vector>
#include "../assertions.hpp"

void testLogin()
{
	assertEquals(1, 2, __FUNCTION__);
}

void testRegister()
{
	assertEquals(1, 1, __FUNCTION__);
}

int main()
{
	int res = 0;
	std::vector<std::function<void()>> tests{
			[]() -> void { testLogin(); },
			[]() -> void { testRegister(); },
	};
	for (auto& test : tests) {
		try {
			test();
		} catch (...) {
			res = 1;
		}
	}

	return res;
}
