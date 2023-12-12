#include "sign_up.h"
#include <iostream>

// enum COMMANDS = []
// enum ARGUMENTS = [NAME, PASSWORD]
namespace crs::command
{
    void sign_up::handle(crs::command::input_parser* input_parser)
    {
        std::cout << "created new user! you can log in now!";
    }

    const std::string sign_up::get_name() const
    {
        return std::string("register");
    }
}



