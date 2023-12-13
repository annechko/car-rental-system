#ifndef LOGIN_H
#define LOGIN_H

#include "abstract_command.h"
#include <core/service/auth_service.h>

namespace crs::console::command
{
    class login : public crs::console::command::abstract_command
    {
        public:
            login();
            void handle(cxxopts::ParseResult& result) override;
            const std::string get_name() const override;
            void configure_options(cxxopts::OptionAdder& options) override;
        private:
            crs::core::service::auth_service* auth_service_;
    };
}

#endif
