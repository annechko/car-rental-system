#ifndef SIGN_UP_H
#define SIGN_UP_H

#include "abstract_command.h"

namespace crs
{
    namespace command
    {
        class sign_up : public crs::command::abstract_command
        {
        protected:
            void handle(crs::command::input_parser* input_parser) override;

            const std::string get_short_name() const override;
            const std::string get_long_name() const override;
        };
    }
}

#endif //SIGN_UP_H
