#include "car_add.h"
#include <ostream>

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

    void car_add::handle(const cxxopts::ParseResult& options, std::ostream& output)
    {
        authenticate(options);

        std::string make = options["make"].as<std::string>();
        std::string model = options["model"].as<std::string>();
        int year = options["year"].as<int>();
        int mileage = options["mileage"].as<int>();
        int min_rent = options["min-rent"].as<int>();
        int max_rent = options["max-rent"].as<int>();
        float price_per_day = options["price-per-day"].as<float>();

        auto car = car_service_->create(make, model, year, mileage, min_rent, max_rent, price_per_day);
        output << "Car " + make + " " + model + " added with ID = " << car->get_id() << "." << std::endl;
    }

    void car_add::configure_options(cxxopts::OptionAdder& options_builder)
    {
        add_auth_params(options_builder)
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
            ("c,price-per-day",
                "Price to rent this car for 1 day.",
                cxxopts::value<float>()->default_value("0"))
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