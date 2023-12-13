#include <iostream>
#include <console/application.h>
#include <list>
#include <cxxopts.hpp>

static const char USAGE[] =
    R"(Naval Fate.

    Usage:
      naval_fate ship new <name>...
      naval_fate ship <name> move <x> <y> [--speed=<kn>]
      naval_fate ship shoot <x> <y>
      naval_fate mine (set|remove) <x> <y> [--moored | --drifting]
      naval_fate (-h | --help)
      naval_fate --version

    Options:
      -h --help     Show this screen.
      --version     Show version.
      --speed=<kn>  Speed in knots [default: 10].
      --moored      Moored (anchored) mine.
      --drifting    Drifting mine.
)";

static const char USAGE_MAIN[] =
    R"(Car Rental System.

    Usage:
      car_rental_system <command> [<args>]

    These are the list of commands:
        user    List, create, or delete users.
        car     List, create, update or delete cars.
        rental  Book a car, calculate the rental fees, manage rental requests.

    See 'car_rental_system help <command>' to read about a specific command.
)";

static const char USAGE_USER[] =
    R"(Car Rental System - user command.

    Usage:
      car_rental_system user - List, create, or delete users.
      car_rental_system user <command> [<args>]

    ? Commands:
        list                        Show all users.
        show <id>                   Show user with ID = <id>.
        add <name> <password>       Add user with specified name and password.
        delete <id>                 Delete user with ID = <id>.
    OR? Options:
        -l, --list                      Show all users.
        -s <id>, --show=<id>            Show user with ID = <id>.
        -a , --add <name> <password>    Add user with specified name and password.
        -d <id>, --delete=<id>          Delete user with ID = <id>.

)";

static const char USAGE_USER_[] =
    R"(
Description:
  User command -

Usage:
  run [options] [--] [<suite> [<test>]]

Arguments:
  suite                                          suite to be tested
  test                                           test to be run

Options:

)";

/*
std::list<crs::command::abstract_command*> get_commands()
{
    std::list<crs::command::abstract_command*> commands;
    commands.push_back(new crs::command::login);
    commands.push_back(new crs::command::sign_up);
    //    commands.push_back(new crs::command::user);//composite
    //    commands.push_back(new crs::command::car);
    return commands;
}
*/
std::string yellow(std::string s)
{
    return "\x1B[1;33m" + s + "\033[0m";
}

std::string green(std::string s)
{
    return "\x1B[1;32m" + s + "\033[0m";
}

int main(int argc, char* argv[])
{
    cxxopts::Options options("car_rental_system " + std::string("<command> ") + std::string("[options]"));
    //    options.add_options("group")
    //        ("d,debug", "Enable debugging");
    options.add_options(green("user:add"))
        //        ("i,integer", "Int param", cxxopts::value<int>())
        //        ("f,file", "File name", cxxopts::value<std::string>())
        ("n,name", "The script file to execute", cxxopts::value<std::string>())
        ("p,password", "The script file to execute", cxxopts::value<std::string>())
        //        ("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))
        ;
    options.add_options(green("user:show"))
        ("i,id", "The script file to execute", cxxopts::value<std::string>())
        //        ("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))
        ;
    //    options.parse_positional({"name","password"});
    options.positional_help("<command>");

    std::string commands_list = "\n";
    commands_list += "  user:add\n";
    commands_list += "  user:show\n";


    options.custom_help(yellow("\n\nAvailable commands:") + green(commands_list) + yellow("\nCommands options:"));
    auto result = options.parse(argc, argv);
    std::cout << options.help(std::vector<std::string>{}) << std::endl;
    //    std::cout << options.help(std::vector<std::string>{std::string("user")}) << std::endl;
    exit(0);
    auto rrr = result["integer"].as<int>();
    // new draft with application as a command.
    auto app = new crs::console::application;
    //    app->handle(new crs::command::input_parser(argv, argv + argc), output);
    app->handle(new crs::console::input_parser(argv, argv + argc));

    return 0;
    /**
     ///



    auto commands = get_commands();

    std::string result;

    //    if no args - show help
    //        (who is responsible? - composite command - list commands?)
    //    ask all commands for their help

    // check for --help here?
    // if there is --help then also check for command name - show all helps or command help
    //    HelpDefinition->createHelp(commands);
    //    HelpDefinition->createHelp(command); // overloading

    // if I handle this specific case here  -> responsibility распыляется

    for (crs::command::abstract_command* c : commands)
    {
        if (c->can_handle(new crs::command::input_parser(argv, argv + argc)))
        {
            result = c->handle(new crs::command::input_parser(argv, argv + argc));
            std::cout << result;
            break;
        }
    }

    *
     *
     *
     * Application itself - is a help composite command having all other commands in itself
     * Application command can either
     *      execute given command
     *      show help of a given command
     *      show help of all commands
     *
     * Application as a command check option --help, or call inner commands to execute
     *
     *
     *
     *
     * */


    //    get help for the application
    /**
     *
     * get all commands and ask them to return their help message
     * composite command asks inner commands
     *
     *
     *
    Description:
      List commands

    Usage:
      list [options] [--] [<namespace>]

    Arguments:
      namespace              The namespace name

    Options:
          --raw              To output raw command list

     *
     */

    //      get help for the command
    /**
 *
 * ask the command to return a help message
 * with
 *
 *
Description:
  Generates empty Cest file in suite

Usage:
  generate:cest <suite> <class>

Arguments:
  suite                  suite where tests will be put
  class                  test name

Options:
  -h, --help             Display help for the given command. When no command is given display help for the list command

 *
 *













    return 0;
     */
}
