#ifndef ABSTRACT_COMMAND_H
#define ABSTRACT_COMMAND_H
#include <string>
#include "input_parser.h"

namespace crs
{
    namespace command
    {
        class abstract_command
        {
        public:
            virtual ~abstract_command()
            {
            }
            bool can_handle(crs::command::input_parser* input_parser);
            virtual std::string handle(crs::command::input_parser* input_parser) = 0;
        protected:
            virtual const std::string get_short_name() const = 0;
            virtual const std::string get_long_name() const = 0;
        };
    }
}


#endif //ABSTRACT_COMMAND_H
