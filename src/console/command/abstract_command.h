#ifndef ABSTRACT_COMMAND_H
#define ABSTRACT_COMMAND_H
#include <string>
#include <list>
#include <ostream>
#include "console/role.hpp"
#include "cxxopts.hpp"
#include "core/service/auth_service.h"

namespace crs::console::command
{
    class abstract_command
    {
        public:
            abstract_command();
            virtual void handle(cxxopts::ParseResult& options, std::ostream& output) = 0;
            virtual const std::string get_name() const = 0;
            virtual const crs::console::ROLE get_permission_level() const = 0;
            virtual void configure_options(cxxopts::OptionAdder& options);
        protected:
            cxxopts::OptionAdder& add_auth_params(cxxopts::OptionAdder& options_builder);
            const void authenticate(const cxxopts::ParseResult& parsed_options);
            crs::core::user::user* user_;
        private:
            static const std::string OPTION_USERNAME;
            static const std::string OPTION_PASSWORD;
            crs::core::service::auth_service* auth_service_;
    };
}


#endif
