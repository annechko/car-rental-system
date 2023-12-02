#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include "../user/user.h"

namespace crs
{
    namespace core
    {
        namespace auth
        {

            class auth_service
            {
            public:
                auth_service();
                crs::core::user::user login(std::string username, std::string password);
            };

        }
    }
}

#endif //AUTH_SERVICE_H
