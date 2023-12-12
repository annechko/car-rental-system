#include "login.h"
#include <iostream>
#include <map>
#include <console/input_parser.h>

namespace crs::console::command
{
    void login::handle(crs::console::input_parser* input_parser)
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


    std::map<std::string> crs::console::command::login::get_arguments()
    {
        return [

        ];
    }*/
}

