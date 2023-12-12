#ifndef LOGIN_H
#define LOGIN_H

#include "abstract_command.h"

namespace crs::command
{
    class login : public crs::command::abstract_command
    {
        public:
            void handle(crs::command::input_parser* input_parser) override;
        protected:
            const std::string get_name() const override;
    };
}

#endif //LOGIN_H
