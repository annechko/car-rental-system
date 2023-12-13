#ifndef APPLICATION_H
#define APPLICATION_H

#include <map>
#include <console/command/abstract_command.h>
#include <cxxopts.hpp>

namespace crs::console
{
    class application
    {
        public:
            application(int argc, const char* const* argv);
            void handle();

        private:
            int argc_;
            const char* const* argv_;
            cxxopts::Options* options_;
            std::map<std::string, crs::console::command::abstract_command*> commands_;
            std::map<std::string, crs::console::command::abstract_command*> build_commands();

            void init_options();
    };

}

#endif