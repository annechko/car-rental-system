#include "abstract_command.h"

bool crs::command::abstract_command::can_handle(crs::command::input_parser* input_parser)
{
    return input_parser->has(this->get_long_name());
}
/*
handle() {
    // check if --help
    // show help???
}
 */