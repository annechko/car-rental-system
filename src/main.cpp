#include <iostream>
#include "console/application.h"
#include "core/core_exception.hpp"
#include "console/text_helper.hpp"

int main(int argc, char* argv[])
{
    std::stringstream output;
    auto app = new crs::console::application(argc, argv, output);

    try
    {
        app->handle();
        std::cout << output.str();
    }
    catch (const std::exception& exception)
    {
        std::cout << crs::console::text_helper::red(exception.what()) << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
