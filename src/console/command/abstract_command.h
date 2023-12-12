#ifndef ABSTRACT_COMMAND_H
#define ABSTRACT_COMMAND_H
#include <string>
#include <console/input_parser.h>

namespace crs::console::command
{
    class abstract_command
    {
        public:
            abstract_command() = default;
            virtual bool can_handle(crs::console::input_parser* input_parser);
            virtual void handle(crs::console::input_parser* input_parser) = 0;
            virtual const std::string get_name() const = 0;
    };
}


#endif
