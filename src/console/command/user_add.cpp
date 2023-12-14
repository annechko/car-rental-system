#include "user_add.h"
#include <iostream>
#include <core/core_exception.h>
#include <core/service/auth_service.h>

namespace crs::console::command
{
    user_add::user_add()
    {
        auth_service_ = new crs::core::service::auth_service;
    }

    const std::string user_add::get_name() const
    {
        return std::string("user:add");
    }

    void user_add::handle(cxxopts::ParseResult& result, std::stringstream& output)
    {
        std::string name = result["name"].as<std::string>();
        std::string pass = result["password"].as<std::string>();
        if (name.empty() || pass.empty())
        {
            throw crs::core::core_exception("Username and password are required.");
        }

        auth_service_->sign_up(name, pass);

        output << "User with username = \"" + name + "\" was created! You can log in now.";
    }

    void user_add::configure_options(cxxopts::OptionAdder& options_builder)
    {
        options_builder
            ("n,name", "Name of new user.", cxxopts::value<std::string>())
            ("p,password", "Password for a new user.", cxxopts::value<std::string>());
    }
}