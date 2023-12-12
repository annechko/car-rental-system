#ifndef USER_ADD_H
#define USER_ADD_H
#include "abstract_command.h"

namespace crs::command
{
    class user_add : public abstract_command
    {
        public:
            const std::string get_name() const override;
            void handle(crs::command::input_parser *input_parser) override;

    };

}


#endif
