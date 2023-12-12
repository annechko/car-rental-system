#include "abstract_composite_command.h"
#include <iostream>
#include <type_traits>

namespace crs::command
{
    void abstract_composite_command::init_commands(std::set<crs::command::abstract_command*> commands)
    {
        commands_ = commands;
    }

    bool abstract_composite_command::can_handle(input_parser* input_parser)
    {
        for (const auto command : commands_)
        {
            if (input_parser->has(get_name() + command->get_name()))
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
            bool is_command_composite = dynamic_cast<crs::command::abstract_composite_command*>(command) != nullptr;
            if (is_command_composite)
            {
                if (command->can_handle(input_parser))
                {
                    command->handle(input_parser);
                }
            }
            else if(input_parser->has(get_name() + command->get_name()))
            {
                command->handle(input_parser);
                return;
            }
        }
    }
}


