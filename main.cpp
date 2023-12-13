#include <iostream>
#include <console/application.h>
#include <list>
#include "core/core_exception.h"

int main(int argc, char* argv[])
{
    auto app = new crs::console::application(argc, argv);

    try
    {
        app->handle();
    }
    catch (const std::exception& exception)
    {
        printf("\x1B[31m");
        std::cout << exception.what() << std::endl;
        printf("\033[0m");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
