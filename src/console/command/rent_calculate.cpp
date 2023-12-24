#include "rent_calculate.h"
#include "console/date_ymd.h"
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

        date_ymd* start_ymd;
        date_ymd* end_ymd;
        try
        {
            start_ymd = new date_ymd(start);
        }
        catch (const core::core_exception& exception)
        {
            throw core::core_exception("Start date: " + std::string(exception.what()));
        }
        try
        {
            end_ymd = new date_ymd(end);
        }
        catch (const core::core_exception& exception)
        {
            throw core::core_exception("End date: " + std::string(exception.what()));
        }

        float total_price = rent_service_->calculate(id, start_ymd, end_ymd);

        output << "Total payment will be (";
        start_ymd->print(output);
        output << " to ";
        end_ymd->print(output);
        output << "): " << total_price << " NZD." << std::endl;
    }

    void rent_calculate::configure_options(cxxopts::OptionAdder& options_builder)
    {
        options_builder
            ("i,id", "Id of the car to book.", cxxopts::value<int>())
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
