#include "application.h"
#include <console/command/abstract_command.h>
#include <console/command/login.h>
#include <console/command/sign_up.h>
#include <console/command/user_add.h>

namespace crs::console
{
    application::application()
    {
        commands_ = build_commands();
    }

    std::set<crs::console::command::abstract_command*> application::build_commands()
    {
        std::set<crs::console::command::abstract_command*> commands;
        commands.insert(new crs::console::command::login);
        commands.insert(new crs::console::command::sign_up);
        commands.insert(new crs::console::command::user_add);
        //    commands.push_back(new crs::command::car);
        return commands;
    }

    void application::handle(input_parser* input_parser)
    {
        for (const auto command : commands_)
        {
            if (command->can_handle(input_parser))
            {
                command->handle(input_parser);

                return;
            }
        }
    }

    //    bool application::can_handle(crs::command::input_parser* input_parser)
    //    {
    //        return abstract_composite_command::can_handle(input_parser);
    //    }
    //
    //    void application::handle(crs::command::input_parser* input_parser)
    //    {
    //        abstract_composite_command::handle(input_parser);
    //    }
}