#ifndef ABSTRACT_COMMAND_H
#define ABSTRACT_COMMAND_H
#include <string>
#include "input_parser.h"

namespace crs::command
{
    class abstract_command
    {
        public:
            abstract_command() = default;
            virtual bool can_handle(crs::command::input_parser* input_parser);
            virtual void handle(crs::command::input_parser* input_parser) = 0;
        protected:
            virtual const std::string get_name() const = 0;
    };
}


#endif
