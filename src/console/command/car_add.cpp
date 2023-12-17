#include "car_add.h"
#include <iostream>
#include <core/core_exception.hpp>

namespace crs::console::command
{
    car_add::car_add()
    {
    }

    const std::string car_add::get_name() const
    {
        return std::string("car:add");
    }

    void car_add::handle(cxxopts::ParseResult& result, std::stringstream& output)
    {
        //        std::string name = result["name"].as<std::string>();
        //        std::string pass = result["password"].as<std::string>();

        output << "Car added!";
    }

    void car_add::configure_options(cxxopts::OptionAdder& options_builder)
    {
        options_builder
            ("k,make", "cv", cxxopts::value<std::string>())
            ("o,model", "cvcv", cxxopts::value<std::string>())
            ("y,year", "xcvc", cxxopts::value<int>())
            ("a,mileage", "sdf", cxxopts::value<int>()->default_value("0"))
            ("min-rent", "The minimum rent period in days.", cxxopts::value<std::string>()->default_value(""))
            ("max-rent", "The maximum rent period in days.", cxxopts::value<std::string>()->default_value(""));
    }

    const crs::console::ROLE car_add::get_permission_level() const
    {
        return crs::console::ROLE::ADMIN;
    }
}