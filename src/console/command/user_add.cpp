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

    void user_add::handle(cxxopts::ParseResult& result)
    {
        std::string name = result["name"].as<std::string>();
        std::string pass = result["password"].as<std::string>();
        if (name.empty() || pass.empty())
        {
            throw crs::core::core_exception("Username and password are required.");
        }

        auth_service_->sign_up(name, pass);

        std::cout << "User with username = \"" + name + "\" was created! You can log in now.";
    }


    /**
    // enum COMMANDS = [ADD, LIST, SHOW]
    // enum ARGUMENTS = [NAME, PASSWORD]
    // extend abstract_composite
    std::set<crs::console::command::abstract_command*> build_commands()
    {
        std::set<crs::console::command::abstract_command*> commands;
        commands.insert(new crs::console::command::user_add);
        commands.insert(new crs::console::command::user_show);
        return commands;
    }

     *
     *
     * // getHelp (){
     * prefix = "user:" // yellow color
     * name = "user\n" // yellow color
     * foreach command in commands
     *        name .= prefix . command->getName() . "\t" . command->getHelp()
     *
     * }
     *
     *
     *
     *
     *
     *
     *
     *





    std::string crs::console::command::sign_up::handle(crs::command::input_parser* input_parser)
    {
        std::cout << "created new user! you can login now!";
    }

    const std::string crs::console::command::sign_up::get_short_name() const
    {
        return std::string("r");
    }

    const std::string crs::console::command::sign_up::get_long_name() const
    {
        return std::string("register");
    }

     */
    // enum OPTIONS = [] // base abstract options always includes -v -q
    // enum ARGUMENTS = [NAME, PASSWORD]
    /*
    std::string crs::console::command::sign_up::execute(crs::command::input_parser* input_parser)
    {
        return "created new user! you can login now!";
    }

    get_arguments_help()
    {
        return [
        ARGUMENTS.NAME => "user name",
            ARGUMENTS.PASSWORD => "user pass",
        ];
    }

    const std::string crs::console::command::sign_up::get_help() const
    {
        return std::string("Create new user");
    }

    const std::string crs::console::command::sign_up::get_name() const
    {
        return std::string("register");
    }*/


    void user_add::configure_options(cxxopts::OptionAdder& options_builder)
    {
        options_builder
            ("n,name", "Name of new user.", cxxopts::value<std::string>())
            ("p,password", "Password for a new user.", cxxopts::value<std::string>());
    }
}