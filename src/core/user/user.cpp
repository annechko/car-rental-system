#include "user.h"

crs::core::user::user::user()
{
}
std::string crs::core::user::user::get_name() const
{
    return std::string("");
}
crs::core::user::ROLE::USER_ROLE crs::core::user::user::get_role() const
{
    return crs::core::user::ROLE::CUSTOMER;
}
