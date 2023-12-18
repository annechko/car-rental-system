#include <iostream>
#include "console/application.h"
#include "core/core_exception.hpp"
#include "console/text_helper.hpp"

int main(int argc, char* argv[])
{
    auto app = new crs::console::application(argc, argv, std::cout);

    try
    {
        app->handle();
    }
    catch (const std::exception& exception)
    {
        std::cout << crs::console::text_helper::red(exception.what()) << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
