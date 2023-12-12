#ifndef LOGIN_H
#define LOGIN_H

#include "abstract_command.h"
#include <console/input_parser.h>

namespace crs::console::command
{
    class login : public crs::console::command::abstract_command
    {
        public:
            void handle(crs::console::input_parser* input_parser) override;
            const std::string get_name() const override;
    };
}

#endif //LOGIN_H
