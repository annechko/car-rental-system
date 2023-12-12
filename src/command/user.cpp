#include "sign_up.h"
#include <iostream>

// enum COMMANDS = [ADD, LIST, SHOW]
// enum ARGUMENTS = [NAME, PASSWORD]
// extend abstract_composite
std::set<crs::command::abstract_command*> build_commands()
{
    std::set<crs::command::abstract_command*> commands;
    commands.insert(new crs::command::user_add);
    commands.insert(new crs::command::user_show);
    return commands;
}
/**
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
 */




std::string crs::command::sign_up::handle(crs::command::input_parser* input_parser)
{
    std::cout << "created new user! you can login now!";
}

const std::string crs::command::sign_up::get_short_name() const
{
    return std::string("r");
}

const std::string crs::command::sign_up::get_long_name() const
{
    return std::string("register");
}

