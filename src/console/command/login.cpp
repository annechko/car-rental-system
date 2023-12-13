#include "login.h"
#include <iostream>
#include <core/core_exception.h>

namespace crs::console::command
{
    login::login()
    {
        auth_service_ = new crs::core::service::auth_service;
    }

    void login::handle(cxxopts::ParseResult& result)
    {
        std::string name = result["name"].as<std::string>();
        std::string pass = result["password"].as<std::string>();
        if (name.empty() || pass.empty())
        {
            throw crs::core::core_exception("Username and password are required.");
        }
        auth_service_->login(name, pass);
        std::cout << "user logged in!";
    }

    const std::string login::get_name() const
    {
        return std::string("login");
    }

    void login::configure_options(cxxopts::OptionAdder& options_builder)
    {
        options_builder
            ("n,name", "Name of user.", cxxopts::value<std::string>())
            ("p,password", "Password for a user.", cxxopts::value<std::string>());
    }
}

