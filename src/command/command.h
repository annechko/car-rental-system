#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include "input_parser.h"

namespace crs
{
    namespace command
    {
        class command
        {
        public:
            virtual ~command()
            {
            }
            bool try_to_handle(crs::command::input_parser* input_parser);
        protected:
            virtual void handle(crs::command::input_parser* input_parser) = 0;
            virtual const std::string get_short_name() const = 0;
            virtual const std::string get_long_name() const = 0;
        };
    }
}


#endif //COMMAND_H
