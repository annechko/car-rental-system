#include "user_add.h"
#include <iostream>

namespace crs::command
{
    const std::string user_add::get_name() const
    {
        return std::string("add");
    }

    void user_add::handle(crs::command::input_parser* input_parser)
    {
        std::cout << "user added!";
    }


    // enum OPTIONS = [] // base abstract options always includes -v -q
    // enum ARGUMENTS = [NAME, PASSWORD]
    /*
    std::string crs::command::sign_up::execute(crs::command::input_parser* input_parser)
    {
        return "created new user! you can login now!";
    }

    const std::string crs::command::sign_up::get_arguments() const
    {
        return ARGUMENTS; // abstract implementation
    }
    get_arguments_help()
    {
        return [
        ARGUMENTS.NAME => "user name",
            ARGUMENTS.PASSWORD => "user pass",
        ];
    }

    const std::string crs::command::sign_up::get_help() const
    {
        return std::string("Create new user");
    }

    const std::string crs::command::sign_up::get_name() const
    {
        return std::string("register");
    }*/


}