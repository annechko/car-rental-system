#ifndef ABSTRACT_COMMAND_H
#define ABSTRACT_COMMAND_H
#include <string>
#include <list>
#include "console/role.hpp"
#include "cxxopts.hpp"

namespace crs::console::command
{
    class abstract_command
    {
        public:
            abstract_command() = default;
            virtual void handle(cxxopts::ParseResult& result, std::stringstream& output) = 0;
            virtual const std::string get_name() const = 0;
            virtual const crs::console::ROLE get_permission_level() const = 0;
            virtual void configure_options(cxxopts::OptionAdder& options);
    };
}


#endif
