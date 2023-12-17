#include "car_add.h"
#include <iostream>
#include <core/core_exception.hpp>

namespace crs::console::command
{
    car_add::car_add()
    {
        car_service_ = new crs::core::service::car_service;
    }

    const std::string car_add::get_name() const
    {
        return std::string("car:add");
    }

    void car_add::handle(cxxopts::ParseResult& result, std::stringstream& output)
    {
        std::string make = result["make"].as<std::string>();
        std::string model = result["model"].as<std::string>();
        int year = result["year"].as<int>();
        int mileage = result["mileage"].as<int>();
        int min_rent = result["min-rent"].as<int>();
        int max_rent = result["max-rent"].as<int>();

        car_service_->create(make, model, year, mileage, min_rent, max_rent);
        output << "Car " + make + " " + model + " added!";
    }

    void car_add::configure_options(cxxopts::OptionAdder& options_builder)
    {
        options_builder
            ("k,make",
                "Company that made a car, for example: Ford, Honda, Volkswagen.",
                cxxopts::value<std::string>())
            ("o,model",
                "Car's specific name, for example: Escape, Civic, or Jetta.",
                cxxopts::value<std::string>())
            ("y,year", "Model year.", cxxopts::value<int>())
            ("a,mileage",
                "Number of miles that car can travel using one gallon of fuel.",
                cxxopts::value<int>()->default_value("0"))
            ("min-rent",
                "The minimum rent period in days.",
                cxxopts::value<int>()->default_value("0"))
            ("max-rent",
                "The maximum rent period in days.",
                cxxopts::value<int>()->default_value("0"));
    }

    const crs::console::ROLE car_add::get_permission_level() const
    {
        return crs::console::ROLE::ADMIN;
    }
}