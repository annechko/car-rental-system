#include "login.h"
#include <iostream>
#include <map>

std::string crs::command::login::handle(crs::command::input_parser* input_parser)
{
    std::cout << "user logged in!";
}

const std::string crs::command::login::get_short_name() const
{
    return std::string("l");
}

const std::string crs::command::login::get_long_name() const
{
    return std::string("login");
}

// enum ARGUMENTS = [NAME, PASSWORD]
// enum COMMANDS = []
/**
 *
 * @return
 */

std::map<std::string> crs::command::login::get_arguments()
{
    return [

        ];
}
