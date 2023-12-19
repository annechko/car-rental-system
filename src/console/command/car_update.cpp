#include "car_update.h"
#include "core/core_exception.hpp"
#include <ostream>

namespace crs::console::command
{
    car_update::car_update()
    {
        car_service_ = new crs::core::service::car_service;
    }

    const std::string car_update::get_name() const
    {
        return std::string("car:update");
    }

    void car_update::handle(cxxopts::ParseResult& options, std::ostream& output)
    {
        authenticate_if_needed(options);

        std::string make = options["make"].as<std::string>();
        std::string model = options["model"].as<std::string>();
        int id = options["id"].as<int>();
        if (id <= 0)
        {
            throw crs::core::core_exception("Id must be greater than 0.");
        }
        int year = options["year"].as<int>();
        int mileage = options["mileage"].as<int>();
        int min_rent = options["min-rent"].as<int>();
        int max_rent = options["max-rent"].as<int>();

        car_service_->update(id, make, model, year, mileage, min_rent, max_rent);
        output << "Car with id = " + std::to_string(id) + " was updated!" << std::endl;
    }

    void car_update::configure_options(cxxopts::OptionAdder& options_builder)
    {
        add_auth_params(options_builder)
            ("i,id", "Id of the car to update.", cxxopts::value<int>())
            ("k,make",
                "Company that made a car, for example: Ford, Honda, Volkswagen.",
                cxxopts::value<std::string>()->default_value(""))
            ("o,model",
                "Car's specific name, for example: Escape, Civic, or Jetta.",
                cxxopts::value<std::string>()->default_value(""))
            ("y,year", "Model year.", cxxopts::value<int>()->default_value("-1"))
            ("a,mileage",
                "Number of miles that car can travel using one gallon of fuel.",
                cxxopts::value<int>()->default_value("-1"))
            ("min-rent",
                "The minimum rent period in days.",
                cxxopts::value<int>()->default_value("-1"))
            ("max-rent",
                "The maximum rent period in days.",
                cxxopts::value<int>()->default_value("-1"));
    }

    const crs::console::ROLE car_update::get_permission_level() const
    {
        return crs::console::ROLE::ADMIN;
    }
}