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

    void sign_up::handle(const cxxopts::ParseResult& options, std::ostream& output)
    {
        std::string name = options["username"].as<std::string>();
        std::string pass = options["password"].as<std::string>();
        bool is_admin = options["admin"].as<bool>();
        if (name.empty() || pass.empty())
        {
            throw crs::core::core_exception("Username and password are required.");
        }

        auth_service_->sign_up(name, pass, is_admin);

        output << "User with username = \"" + name + "\" was created! You can log in now." << std::endl;
    }

    void sign_up::configure_options(cxxopts::OptionAdder& options_builder)
    {
        options_builder
            ("u,username", "Username for a new user.", cxxopts::value<std::string>())
            ("p,password", "Password for a new user.", cxxopts::value<std::string>())
            ("a,admin", "Assign admin permissions (testing purposes).");
    }

    const crs::console::ROLE sign_up::get_permission_level() const
    {
        return crs::console::ROLE::ANY;
    }
}



