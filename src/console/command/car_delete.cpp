#include "car_delete.h"
#include "core/core_exception.hpp"
#include <ostream>

namespace crs::console::command
{
    car_delete::car_delete()
    {
        car_service_ = new crs::core::service::car_service;
    }

    const std::string car_delete::get_name() const
    {
        return std::string("car:delete");
    }

    void car_delete::handle(cxxopts::ParseResult& options, std::ostream& output)
    {
        authenticate(options);

        int id = options["id"].as<int>();
        if (id <= 0)
        {
            throw crs::core::core_exception("Id must be greater than 0.");
        }

        car_service_->delete_car(id);
        output << "Car with id = " + std::to_string(id) + " was deleted!" << std::endl;
    }

    void car_delete::configure_options(cxxopts::OptionAdder& options_builder)
    {
        add_auth_params(options_builder)
            ("i,id", "Id of the car to update.", cxxopts::value<int>());
    }

    const crs::console::ROLE car_delete::get_permission_level() const
    {
        return crs::console::ROLE::ADMIN;
    }
}