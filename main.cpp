#include <iostream>
#include <console/application.h>
#include <list>
#include "core/core_exception.h"

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

int main(int argc, char* argv[])
{
    auto app = new crs::console::application(argc, argv);

    try
    {
        app->handle();
    }
    catch (crs::core::core_exception& exception)
    {
        printf("\x1B[31m");
        std::cout << exception.what() << std::endl;
        printf("\033[0m");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
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
