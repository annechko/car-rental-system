#include "application.h"
#include <console/command/abstract_command.h>
#include <console/command/login.h>
#include <console/command/sign_up.h>
#include <console/command/user_add.h>
#include <core/core_exception.h>
#include <cxxopts.hpp>
#include <set>
#include <iostream>

namespace crs::console
{
    std::string yellow(std::string s)
    {
        return "\x1B[1;33m" + s + "\033[0m";
    }

    std::string green(std::string s)
    {
        return "\x1B[1;32m" + s + "\033[0m";
    }

    application::application(int argc, const char* const* argv)
    {
        argc_ = argc;
        argv_ = argv;
        init_commands();
        init_options();
    }

    void application::init_commands()
    {
        std::set<crs::console::command::abstract_command*> commands;
        commands.insert(new crs::console::command::login);
        commands.insert(new crs::console::command::sign_up);
        commands.insert(new crs::console::command::user_add);

        for (crs::console::command::abstract_command* command : commands)
        {
            commands_[command->get_name()] = command;
        }
    }

    void application::init_options()
    {
        for (const auto& [key, command] : commands_)
        {
            auto command_options = new cxxopts::Options(green("car_rental_system " + command->get_name()));

            auto builder = command_options->add_options();
            command->configure_options(builder);
            options_commands[command->get_name()] = command_options;
        }

        options_default_ = new cxxopts::Options(green("car_rental_system <command> [options]"));
        options_default_->positional_help("");
        options_default_->allow_unrecognised_options();
        options_default_->custom_help("");
        options_default_->add_options()
            ("command", "The command to execute.", cxxopts::value<std::string>()->default_value(""))
            ("h,help", "Print help.")
            ("u,username", "Login as user.", cxxopts::value<std::string>())
            ("p,password", "Login password.", cxxopts::value<std::string>());
        options_default_->parse_positional({ "command" });
    }

    void application::handle()
    {
        auto parsed_options = options_default_->parse(argc_, argv_);
        std::string command_name = parsed_options["command"].as<std::string>();
        bool has_help_option = parsed_options["help"].count() > 0;

        if (!command_name.empty() && !commands_.contains(command_name))
        {
            throw crs::core::core_exception("Command \"" + command_name + "\" does not exist!");
        }

        if (has_help_option)
        {
            std::cout << options_default_->help() << std::endl;
            if (!command_name.empty())
            {
                std::cout << options_commands.find(command_name)->second->help() << std::endl;
            }
            else
            {
                for (const auto [k, cmd] : options_commands)
                {
                    std::cout << cmd->help() << std::endl;
                }
            }
            return;
        }

        if (command_name.empty())
        {
            throw crs::core::core_exception("Please specify <command>.");
        }

        auto parsed_cmnd_options = options_commands[command_name]->parse(argc_, argv_);
        commands_[command_name]->handle(parsed_cmnd_options);
    }
}