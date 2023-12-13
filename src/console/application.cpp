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
        commands_ = build_commands();

        init_options();
    }

    std::map<std::string, crs::console::command::abstract_command*> application::build_commands()
    {
        std::set<crs::console::command::abstract_command*> commands;
        commands.insert(new crs::console::command::login);
        commands.insert(new crs::console::command::sign_up);
        commands.insert(new crs::console::command::user_add);
        std::map<std::string, crs::console::command::abstract_command*> result;
        for (crs::console::command::abstract_command* command : commands)
        {
            result.insert({ command->get_name(), command });
        }
        return result;
    }

    void application::init_options()
    {
        options_ = new cxxopts::Options((std::string)"car_rental_system <command> [options]");
        options_->positional_help("");
        std::string commands_list = "\n";

        for (const auto command : commands_)
        {
            commands_list += "  " + command.second->get_name() + "\n";
        }
        options_->custom_help(
            yellow("\n\nAvailable commands:") + green(commands_list) + yellow("\nCommands options:")
        );

        for (const auto command : commands_)
        {
            auto builder = options_->add_options(command.second->get_name());
            command.second->configure_options(builder);
        }

        options_->add_options()
            ("command", "The command to execute.", cxxopts::value<std::string>()->default_value(""))
            ("h,help", "Print help.");
        options_->parse_positional({ "command" });
    }

    void application::handle()
    {
        auto parsed_options = options_->parse(argc_, argv_);
        std::string command_name = parsed_options["command"].as<std::string>();
        bool has_help_option = parsed_options["help"].count() > 0;

        if (!command_name.empty() && !commands_.contains(command_name))
        {
            throw crs::core::core_exception("Command \"" + command_name + "\" does not exist!");
        }

        if (has_help_option)
        {
            std::vector<std::string> command_name_for_help;
            if (!command_name.empty())
            {
                command_name_for_help.push_back(command_name);
                options_->custom_help("");
            }
            std::cout << options_->help(command_name_for_help) << std::endl;
            return;
        }

        if (command_name.empty())
        {
            throw crs::core::core_exception("Please specify <command>.");
        }

        commands_.find(command_name)->second->handle();
    }

    //
    //    void application::handle(crs::command::input_parser* input_parser)
    //    {
    //        abstract_composite_command::handle(input_parser);
    //    }
}