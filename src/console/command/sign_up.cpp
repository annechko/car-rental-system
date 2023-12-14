#include "sign_up.h"
#include <iostream>

// enum COMMANDS = []
// enum ARGUMENTS = [NAME, PASSWORD]
namespace crs::console::command
{
    void sign_up::handle(cxxopts::ParseResult& result, std::stringstream& output)
    {
        output << "created new user! you can log in now!";
    }

    const std::string sign_up::get_name() const
    {
        return std::string("register");
    }
}



