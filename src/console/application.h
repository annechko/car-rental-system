#ifndef APPLICATION_H
#define APPLICATION_H

#include <map>
#include <console/command/abstract_command.h>
#include <cxxopts.hpp>
#include <ostream>

namespace crs::console
{
    class application
    {
        public:
            application(const int argc, const char* const* argv, std::ostream& output);
            void handle();

        private:
            const int argc_;
            const char* const* argv_;
            std::ostream& output_;
            std::unordered_map<std::string, cxxopts::Options*> options_commands;
            cxxopts::Options* options_default_;
            std::unordered_map<std::string, crs::console::command::abstract_command*> commands_;
            void init_commands();
            void init_options();
    };

}

#endif