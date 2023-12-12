#ifndef APPLICATION_H
#define APPLICATION_H

#include "abstract_composite_command.h"
#include <set>

namespace crs::command
{
    class application : public crs::command::abstract_composite_command
    {
        public:
            application();
            // all other commands are here
            //            bool can_handle(crs::command::input_parser* input_parser) override;
            //            void handle(crs::command::input_parser *input_parser) override;
            const std::string get_name() const override;
        private:
            std::set<crs::command::abstract_command*> build_commands();

    };

}

#endif