#include "abstract_command.h"
#include <console/role.hpp>
#include <cxxopts.hpp>
#include <core/core_exception.hpp>

namespace crs::console::command
{
    const std::string abstract_command::OPTION_USERNAME = "username";

    const std::string abstract_command::OPTION_PASSWORD = "password";

    abstract_command::abstract_command()
    {
        auth_service_ = new crs::core::service::auth_service;
        user_ = nullptr;
    }

    void abstract_command::configure_options(cxxopts::OptionAdder& options)
    {
    }

    cxxopts::OptionAdder& abstract_command::add_auth_params(
        cxxopts::OptionAdder& options_builder
    )
    {
        return options_builder
            ("u," + OPTION_USERNAME, "Login as user.", cxxopts::value<std::string>()->default_value(""))
            ("p," + OPTION_PASSWORD, "Login password.", cxxopts::value<std::string>()->default_value(""));
    }

    const void abstract_command::authenticate(const cxxopts::ParseResult& parsed_options)
    {
        auto required_role = get_permission_level();
        if (required_role == ROLE::ANY)
        {
            return;
        }

        std::string username = parsed_options[OPTION_USERNAME].as<std::string>();
        std::string password = parsed_options[OPTION_PASSWORD].as<std::string>();
        if (username.empty() || password.empty())
        {
            throw crs::core::core_exception(
                "Authentication is required to run this command (" + get_name()
                    + "), please provide username and password options.");
        }

        crs::core::user::user* user = auth_service_->login(username, password);
        user_ = user;
        switch (required_role)
        {
            case ROLE::AUTHENTICATED:
            case ROLE::ANY:
                break;
            case ROLE::ADMIN:
                if (!user->is_admin())
                {
                    throw crs::core::core_exception("This command can be run only by admin user.");
                }
                break;
            case ROLE::CUSTOMER:
                if (!user->is_customer())
                {
                    throw crs::core::core_exception("Command can be run only by customer user.");
                }
                break;
        }
        return;
    }
}
