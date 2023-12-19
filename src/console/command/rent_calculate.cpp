#include "rent_calculate.h"
#include "core/core_exception.hpp"
#include <string>

namespace crs::console::command
{
    rent_calculate::rent_calculate()
    {
        rent_service_ = new crs::core::service::rent_service;
    }

    const std::string rent_calculate::get_name() const
    {
        return std::string("rent:calculate");
    }

    void rent_calculate::handle(cxxopts::ParseResult& options, std::ostream& output)
    {
        int id = options["id"].as<int>();
        if (id <= 0)
        {
            throw crs::core::core_exception("Id must be greater than 0.");
        }
        std::string start = options["start"].as<std::string>();
        std::string end = options["end"].as<std::string>();


        output << "Your price will be: " << std::endl;
    }

    void rent_calculate::configure_options(cxxopts::OptionAdder& options_builder)
    {
        options_builder
            ("i,id", "Id of the car to update.", cxxopts::value<int>())
            ("s,start",
                "From which date you want to book a car, format dd/mm/yyy: 31/12/2020.",
                cxxopts::value<std::string>())
            ("e,end",
                "Until when you want to book a car, format dd/mm/yyy: 31/12/2020.",
                cxxopts::value<std::string>());
    }

    const crs::console::ROLE rent_calculate::get_permission_level() const
    {
        return crs::console::ROLE::ANY;
    }
}
