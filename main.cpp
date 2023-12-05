#include <iostream>
#include <vector>
#include <command/command.h>
#include <command/login.h>
#include <command/sign_up.h>
#include <list>

using std::cout;
using std::endl;
/*
char* getCmdOption(char** begin_, char** end_, const std::string& option)
{
    char** itr = std::find(begin_, end_, option);
    if (itr != end_ && ++itr != end_)
    {
        return *itr;
    }
    return 0;
}
*/
int main(int argc, char* argv[])
{
    std::list<crs::command::command*> commands;
    commands.push_back(new crs::command::login);
    commands.push_back(new crs::command::sign_up);

    for (crs::command::command* c : commands)
    {
        if (c->try_to_handle(new crs::command::input_parser(argv, argv + argc)))
        {
            break;
        }
    }


    //    char* filename = getCmdOption(argv, argv + argc, "-f");

    //    if (filename)
    //    {
    //        std::cout << "// Do interesting things filename: " << filename;
    //
    //    }

    return 0;
    //    crs::core::user::user_repository repo;
    //    repo.get_by_id(3);

}