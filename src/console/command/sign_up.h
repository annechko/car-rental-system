#ifndef SIGN_UP_H
#define SIGN_UP_H

#include "abstract_command.h"
#include <core/service/auth_service.h>

namespace crs::console::command
{
    class sign_up : public crs::console::command::abstract_command
    {
        public:
            sign_up();
            void handle(cxxopts::ParseResult& result, std::ostream& output) override;
            const std::string get_name() const override;
            void configure_options(cxxopts::OptionAdder& options) override;
            const crs::console::ROLE get_permission_level() const override;
        private:
            crs::core::service::auth_service* auth_service_;
    };
}

#endif //SIGN_UP_H
