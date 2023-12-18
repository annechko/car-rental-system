#include "application.h"
#include <console/command/abstract_command.h>
#include <console/command/sign_up.h>
#include <console/command/car_add.h>
#include <console/command/car_list.h>
#include <console/role.hpp>
#include <console/text_helper.hpp>
#include <core/core_exception.hpp>
#include <cxxopts.hpp>
#include <set>
#include <ostream>

namespace crs::console
{
    application::application(int argc, const char* const* argv, ostream& output)
        : output_(output)
    {
        argc_ = argc;
        argv_ = argv;
        auth_service_ = new crs::core::service::auth_service;
        init_commands();
        init_options();
    }

    void application::init_commands()
    {
        std::set<crs::console::command::abstract_command*> commands;
        commands.insert(new crs::console::command::sign_up);
        commands.insert(new crs::console::command::car_add);
        commands.insert(new crs::console::command::car_list);

        for (crs::console::command::abstract_command* command : commands)
        {
            commands_[command->get_name()] = command;
        }
    }

    void application::init_options()
    {
        for (const auto& [key, command] : commands_)
        {
            auto command_options = new cxxopts::Options(text_helper::green(
                (std::string)"car_rental_system " + command->get_name()));
            command_options->allow_unrecognised_options();

            auto builder = command_options->add_options();
            command->configure_options(builder);
            options_commands[command->get_name()] = command_options;
        }

        options_default_ = new cxxopts::Options(
            ((std::string)"car_rental_system <command> [options]"),
            "Car Rental System - help with the rental process, users and cars management."
        );
        options_default_->positional_help("");
        options_default_->allow_unrecognised_options();
        options_default_->custom_help("");
        // todo maybe move -u -p to abstract command for every command that needs auth
        options_default_->add_options()
            ("command", "The command to execute.", cxxopts::value<std::string>()->default_value(""))
            ("h,help", "Print help.")
            ("u,username", "Login as user.", cxxopts::value<std::string>()->default_value(""))
            ("p,password", "Login password.", cxxopts::value<std::string>()->default_value(""));
        options_default_->parse_positional({ "command" });
    }

    void application::handle()
    {
        auto parsed_options = options_default_->parse(argc_, argv_);
        std::string command_name = parsed_options["command"].as<std::string>();
        bool has_help_option = parsed_options["help"].count() > 0;
        if (command_name == "" && argc_ == 1)
        {
            // by default always show help.
            has_help_option = true;
        }
        if (!command_name.empty() && !commands_.contains(command_name))
        {
            throw crs::core::core_exception("Command \"" + command_name + "\" does not exist!");
        }

        if (has_help_option)
        {
            output_ << options_default_->help() << std::endl;
            if (!command_name.empty())
            {
                output_ << options_commands.find(command_name)->second->help() << std::endl;
            }
            else
            {
                for (const auto [k, cmd] : options_commands)
                {
                    output_ << cmd->help() << std::endl;
                }
            }
            return;
        }

        if (command_name.empty())
        {
            throw crs::core::core_exception("Please specify <command>.");
        }

        auto parsed_cmnd_options = options_commands[command_name]->parse(argc_, argv_);
        auto command = commands_[command_name];
        authenticate_if_needed(command->get_permission_level(), parsed_options);
        command->handle(parsed_cmnd_options, output_);
    }

    void application::authenticate_if_needed(ROLE required_role, const cxxopts::ParseResult& parsed_options)
    {
        if (required_role == ROLE::ANONYMOUS)
        {
            return;
        }

        std::string username = parsed_options["username"].as<std::string>();
        std::string password = parsed_options["password"].as<std::string>();
        if (username.empty() || password.empty())
        {
            throw crs::core::core_exception(
                "Authentication is required to run this command, please provide username and password options.");
        }

        crs::core::user::user* user = auth_service_->login(username, password);
        switch (required_role)
        {
            case ROLE::AUTHENTICATED:
            case ROLE::ANONYMOUS:
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