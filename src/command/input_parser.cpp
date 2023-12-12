#include <algorithm>
#include "input_parser.h"

namespace crs::command
{
    bool input_parser::has(std::string name)
    {
        return cmd_option_exists(begin_, end_, name);
    }

    bool input_parser::cmd_option_exists(char** begin, char** end, const std::string& option)
    {
        return std::find(begin, end, option) != end;
    }
}