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
            crs::core::user::user get_by_id(int id);
            void save(crs::core::user::user user_to_add);
    };
}

#endif //USER_REPOSITORY_H
