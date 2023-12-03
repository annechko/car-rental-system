#include "user.h"
#include "../core_exception.h"

crs::core::user::ROLE::USER_ROLE crs::core::user::user::get_role() const
{
    return crs::core::user::ROLE::CUSTOMER;
}
crs::core::user::user::user(std::string name)
{
    validate_name(name);
    name_ = name;
}
void crs::core::user::user::validate_name(std::string username)
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
