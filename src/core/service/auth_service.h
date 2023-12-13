#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include <core/user/user.h>
#include <core/user/user_repository.h>

namespace crs::core::service
{
    class auth_service
    {
        public:
            auth_service();
            crs::core::user::user* login(std::string username, std::string password);
            crs::core::user::user* sign_up(std::string username, std::string password);
        private:
            crs::core::user::user_repository* user_repository_;
    };
}

#endif
