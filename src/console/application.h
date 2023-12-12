#ifndef APPLICATION_H
#define APPLICATION_H

#include <set>
#include <console/command/abstract_command.h>

namespace crs::console
{
    class application
    {
        public:
            application();
            void handle(crs::console::input_parser* input_parser);

        private:
            std::set<crs::console::command::abstract_command*> commands_;
            std::set<crs::console::command::abstract_command*> build_commands();

    };

}

#endif