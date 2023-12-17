#include "auth_service.h"
#include <core/user/user.h>
#include <core/core_exception.hpp>
#include "bcrypt.h"

namespace crs::core::service
{
    auth_service::auth_service()
    {
        user_repository_ = new crs::core::user::user_repository;
    }

    crs::core::user::user* auth_service::login(std::string username, std::string password)
    {
        crs::core::user::user* user = user_repository_->get_by_username(username);
        if (!bcrypt::validatePassword(password, user->get_password_hash()))
        {
            throw core::core_exception("Password is invalid!");
        }
        return user;
    }

    crs::core::user::user* auth_service::sign_up(std::string username, std::string password)
    {
        auto user = new crs::core::user::user(username, bcrypt::generateHash(password));
        user_repository_->save(user);

        return user;
    }
}

