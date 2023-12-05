#ifndef LOGIN_H
#define LOGIN_H

#include "command.h"

namespace crs
{
    namespace command
    {
        class login : public crs::command::command
        {
        protected:
            void handle(crs::command::input_parser* input_parser) override;

            const std::string get_short_name() const override;
            const std::string get_long_name() const override;
        };

    } // crs
} // command

#endif //LOGIN_H
