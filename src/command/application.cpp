#include "abstract_command.h"
#include <set>
// composite command

// all other commands are here
std::set<crs::command::abstract_command*> build_commands()
{
    std::set<crs::command::abstract_command*> commands;
    commands.insert(new crs::command::login);
    commands.insert(new crs::command::sign_up);
    //    commands.push_back(new crs::command::user);//composite
    //    commands.push_back(new crs::command::car);
    return commands;
}

// check for option --help
// has option
    // check command name
        // has command - draw command help
        // no command - ask all commands for help
        // return

// no --help option
    // parent execute

    // foreach commands
        // can handle?
            // execute

    // foreach commands
        // if execute break






// typical command execute
    // canHandle ?
        // yes - call execute
        // no - return