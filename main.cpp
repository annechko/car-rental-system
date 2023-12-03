#include <iostream>
#include <core/user/user_repository.h>

using std::cout;
using std::endl;

int main(int, char**)
{
    crs::core::user::user_repository repo;
    repo.get_by_id(3);

    return 0;
}