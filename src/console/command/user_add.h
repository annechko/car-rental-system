#ifndef USER_ADD_H
#define USER_ADD_H
#include "abstract_command.h"
#include <core/service/auth_service.h>

namespace crs::console::command
{
    class user_add : public abstract_command
    {
        public:
            user_add();
            const std::string get_name() const override;
            void handle(cxxopts::ParseResult& result, std::stringstream& output) override;
            void configure_options(cxxopts::OptionAdder& options) override;
        private:
            crs::core::service::auth_service* auth_service_;
    };

}


#endif
