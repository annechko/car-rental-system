#ifndef APPLICATION_H
#define APPLICATION_H

#include <map>
#include <console/command/abstract_command.h>
#include <cxxopts.hpp>
#include <sstream>

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
            void init_commands();
            void init_options();
    };

}

#endif