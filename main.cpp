#include <iostream>
#include "command/abstract_command.h"
#include <command/login.h>
#include <command/sign_up.h>
#include <list>

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    std::list<crs::command::abstract_command*> commands;
    commands.push_back(new crs::command::login);
    commands.push_back(new crs::command::sign_up);

    for (crs::command::abstract_command* c : commands)
    {
        if (c->try_to_handle(new crs::command::input_parser(argv, argv + argc)))
        {
            break;
        }
    }

    return 0;
}