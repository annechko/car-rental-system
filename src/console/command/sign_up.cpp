#include "sign_up.h"
#include <iostream>
#include <console/input_parser.h>

// enum COMMANDS = []
// enum ARGUMENTS = [NAME, PASSWORD]
namespace crs::console::command
{
    void sign_up::handle(crs::console::input_parser* input_parser)
    {
        std::cout << "created new user! you can log in now!";
    }

    const std::string sign_up::get_name() const
    {
        return std::string("register");
    }
}



