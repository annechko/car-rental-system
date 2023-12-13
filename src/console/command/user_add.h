#ifndef USER_ADD_H
#define USER_ADD_H
#include "abstract_command.h"

namespace crs::console::command
{
    class user_add : public abstract_command
    {
        public:
            const std::string get_name() const override;
            void handle() override;
            void configure_options(cxxopts::OptionAdder& options) override;
    };

}


#endif
