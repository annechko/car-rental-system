#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H
#include "user.h"

namespace crs::core::user
{
    class user_repository
    {
        public:
            user_repository()
            {
            };
            user* get_by_id(int id);
            user get_by_username(std::string username);
            void save(user* user_to_add);
    };
}

#endif //USER_REPOSITORY_H
