#include "abstract_command.h"

namespace crs::command
{
    bool abstract_command::can_handle(crs::command::input_parser* input_parser)
    {
        return input_parser->has(this->get_name());
    }
}

/*
handle() {
    // check if --help
    // show help???
}
 */