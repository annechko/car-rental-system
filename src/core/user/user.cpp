#include "user.h"
#include <core/core_exception.h>

namespace crs::core::user
{
    const std::string user::get_name() const
    {
        return name_;
    }

    const std::string user::get_password_hash() const
    {
        return password_hash_;
    }

    const crs::core::user::USER_ROLE user::get_role() const
    {
        return crs::core::user::USER_ROLE::CUSTOMER;
    }

    user::user(std::string name, std::string password_hash)
    {
        validate_name(name);
        name_ = name;
        password_hash_ = password_hash;
    }

    void user::validate_name(std::string username)
    {
        int length = username.length();
        if (length == 0)
        {
            throw crs::core::core_exception("Username can not be empty.");
        }
        else if (length > crs::core::user::MAX_NAME_LENGTH)
        {
            throw crs::core::core_exception("Username too long.");
        }

        for (int i = 0; i < length; i++)
        {
            char letter = username.at(i);
            if (!(isalnum(letter) || letter == '_'))
            {
                throw crs::core::core_exception("Username is invalid.");
            }
        }
    }

}
