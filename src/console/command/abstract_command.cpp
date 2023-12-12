#include "abstract_command.h"
#include <console/input_parser.h>

namespace crs::console::command
{
    bool abstract_command::can_handle(crs::console::input_parser* input_parser)
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