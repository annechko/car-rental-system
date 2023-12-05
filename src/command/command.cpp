#include <algorithm>
#include "command.h"

bool crs::command::command::try_to_handle(crs::command::input_parser* input_parser)
{
    if (input_parser->has(this->get_long_name()))
    {
        this->handle(input_parser);
        return true;
    }
    else
    {
        return false;
    }
}
