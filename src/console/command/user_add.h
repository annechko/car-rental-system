#ifndef USER_ADD_H
#define USER_ADD_H
#include "abstract_command.h"
#include <console/input_parser.h>

namespace crs::console::command
{
    class user_add : public abstract_command
    {
        public:
            const std::string get_name() const override;
            void handle(crs::console::input_parser *input_parser) override;

    };

}


#endif
