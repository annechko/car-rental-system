#include "sign_up.h"
#include <iostream>

// enum COMMANDS = []
// enum ARGUMENTS = [NAME, PASSWORD]

std::string crs::command::sign_up::handle(crs::command::input_parser* input_parser)
{
    std::cout << "created new user! you can login now!";
}

const std::string crs::command::sign_up::get_short_name() const
{
    return std::string("r");
}

const std::string crs::command::sign_up::get_long_name() const
{
    return std::string("register");
}

