#ifndef SIGN_UP_H
#define SIGN_UP_H

#include "abstract_command.h"

namespace crs
{
    namespace command
    {
        class sign_up : public crs::command::abstract_command
        {
        public:
            std::string handle(crs::command::input_parser* input_parser) override;
        protected:

            const std::string get_short_name() const override;
            const std::string get_long_name() const override;
        };
    }
}

#endif //SIGN_UP_H
