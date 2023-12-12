#include "login.h"
#include <iostream>
#include <map>

namespace crs::command
{
    void login::handle(crs::command::input_parser* input_parser)
    {
        std::cout << "user logged in!";
    }

    const std::string login::get_name() const
    {
        return std::string("login");
    }

    // enum ARGUMENTS = [NAME, PASSWORD]
    // enum COMMANDS = []
    /**
     *
     *


    std::map<std::string> crs::command::login::get_arguments()
    {
        return [

        ];
    }*/
}

