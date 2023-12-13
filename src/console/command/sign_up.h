#ifndef SIGN_UP_H
#define SIGN_UP_H

#include "abstract_command.h"

namespace crs::console::command
{
    class sign_up : public crs::console::command::abstract_command
    {
        public:
            void handle() override;
            const std::string get_name() const override;
    };
}

#endif //SIGN_UP_H
