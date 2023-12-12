#include "abstract_composite_command.h"
#include <iostream>

namespace crs::command
{
    bool abstract_composite_command::can_handle(input_parser* input_parser)
    {
        for (const auto command : commands_)
        {
            if (command->can_handle(input_parser))
            {
                return true;
            }
        }
        return false;
    }

    void abstract_composite_command::handle(input_parser* input_parser)
    {
        for (const auto command : commands_)
        {
            if (command->can_handle(input_parser))
            {
                command->handle(input_parser);
                return;
            }
        }
    }

    void abstract_composite_command::init_commands(std::set<crs::command::abstract_command*> commands)
    {
        commands_ = commands;
    }
}


