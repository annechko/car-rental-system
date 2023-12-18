#include "user.h"
#include <core/core_exception.hpp>
#include <unordered_map>

namespace crs::core::user
{
    user::user(std::string name, std::string password_hash)
    {
        validate_name(name);
        id_ = 0;
        name_ = name;
        password_hash_ = password_hash;
        role_ = crs::core::user::USER_ROLE::CUSTOMER;
    }

    user::user()
    {
        // will be called by sqlite lib.
        id_ = 0;
        name_ = "";
        password_hash_ = "";
        role_ = crs::core::user::USER_ROLE::CUSTOMER;
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

    const std::string user::get_name() const
    {
        return name_;
    }

    void user::set_name(const std::string& name)
    {
        name_ = name;
    }

    const std::string user::get_password_hash() const
    {
        return password_hash_;
    }

    void user::set_password_hash(const std::string& password_hash)
    {
        password_hash_ = password_hash;
    }

    const crs::core::user::USER_ROLE user::get_role() const
    {
        return role_;
    }

    void user::set_role_value(int role)
    {
        if (role == 0)
        {
            role_ = USER_ROLE::CUSTOMER;
        }
        else
        {
            role_ = USER_ROLE::ADMIN;
        }
    }

    const int user::get_id() const
    {
        return id_;
    }

    void user::set_id(int id)
    {
        id_ = id;
    }

    const int user::get_role_value() const
    {
        if (role_ == USER_ROLE::CUSTOMER)
        {
            return 0;
        }
        return 1;
    }

    void user::make_admin()
    {
        role_ = USER_ROLE::ADMIN;
    }
}
