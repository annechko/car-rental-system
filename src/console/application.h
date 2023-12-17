#ifndef APPLICATION_H
#define APPLICATION_H

#include <map>
#include <console/command/abstract_command.h>
#include <cxxopts.hpp>
#include <sstream>
#include <core/service/auth_service.h>

namespace crs::console
{
    class application
    {
        public:
            application(int argc, const char* const* argv, std::stringstream& output);
            void handle();

        private:
            int argc_;
            const char* const* argv_;
            std::stringstream& output_;
            std::unordered_map<std::string, cxxopts::Options*> options_commands;
            cxxopts::Options* options_default_;
            std::unordered_map<std::string, crs::console::command::abstract_command*> commands_;
            crs::core::service::auth_service* auth_service_;
            void init_commands();
            void init_options();
            void authenticate_if_needed(ROLE required_role, const cxxopts::ParseResult& parsed_options);
    };

}

#endif