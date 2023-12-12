#include "abstract_command.h"

// in constructor virtual "init commands" method - every child has to implement
// virtual "build commands" method - in constructor: commands = build commands

bool crs::command::abstract_composite_command::can_handle(crs::command::input_parser* input_parser)
{
    for (const auto& command : commands_)
    {
        if (input_parser->has(command->get_long_name()))
        {
            return true;
        }
    }
    return false;
}
