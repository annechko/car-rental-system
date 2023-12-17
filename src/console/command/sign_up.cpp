#include "sign_up.h"
#include <iostream>
#include <core/core_exception.hpp>
#include <core/service/auth_service.h>

namespace crs::console::command
{
    sign_up::sign_up()
    {
        auth_service_ = new crs::core::service::auth_service;
    }

    const std::string sign_up::get_name() const
    {
        return std::string("register");
    }

    void sign_up::handle(cxxopts::ParseResult& result, std::stringstream& output)
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

    void sign_up::configure_options(cxxopts::OptionAdder& options_builder)
    {
        options_builder
            ("n,name", "Name of new user.", cxxopts::value<std::string>())
            ("p,password", "Password for a new user.", cxxopts::value<std::string>());
    }

    const crs::console::ROLE sign_up::get_permission_level() const
    {
        return crs::console::ROLE::ANONYMOUS;
    }
}



