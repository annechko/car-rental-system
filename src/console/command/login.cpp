#include "login.h"
#include <iostream>

namespace crs::console::command
{
    void login::handle()
    {
        std::cout << "user logged in!";
    }

    const std::string login::get_name() const
    {
        return std::string("login");
    }

    // enum ARGUMENTS = [NAME, PASSWORD]
    // enum COMMANDS = []
}

