#include "application.h"
#include "login.h"
#include "sign_up.h"
#include "user.h"

namespace crs::command
{
    std::set<crs::command::abstract_command*> application::build_commands()
    {
        std::set<crs::command::abstract_command*> commands;
        commands.insert(new crs::command::login);
        commands.insert(new crs::command::sign_up);
        commands.insert(new crs::command::user);//composite
        //    commands.push_back(new crs::command::car);
        return commands;
    }

    application::application()
    {
        init_commands(build_commands());
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

    const std::string application::get_name() const
    {
        return "";
    }
}