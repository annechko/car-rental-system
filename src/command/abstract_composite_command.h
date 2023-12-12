#ifndef ABSTRACT_COMPOSITE_COMMAND_H
#define ABSTRACT_COMPOSITE_COMMAND_H
#include "abstract_command.h"
#include "input_parser.h"
#include <set>
#include <iostream>
namespace crs::command
{
    class abstract_composite_command : public crs::command::abstract_command
    {
        public:
            void handle(crs::command::input_parser* input_parser) override;
            bool can_handle(crs::command::input_parser* input_parser) override;
        protected:
            void init_commands(std::set<crs::command::abstract_command*>);

        private:
            std::set<crs::command::abstract_command*> commands_;
    };
}


#endif
