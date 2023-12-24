#include "car_book.h"
#include "console/date_ymd.h"
#include "core/core_exception.hpp"
#include <string>

namespace crs::console::command
{
    car_book::car_book()
    {
        rent_service_ = new crs::core::service::rent_service;
    }

    const std::string car_book::get_name() const
    {
        return std::string("booking:add");
    }

    void car_book::handle(cxxopts::ParseResult& options, std::ostream& output)
    {
        authenticate_if_needed(options);

        int id = options["id"].as<int>();
        if (id <= 0)
        {
            throw crs::core::core_exception("Id must be greater than 0.");
        }
        if (user_id_ <= 0)
        {
            throw crs::core::core_exception("User Id must be greater than 0.");
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

        auto total = rent_service_->book(user_id_, id, start_ymd, end_ymd);

        output << "Car has successfully been booked, the payment will be " << total << " NZD." << std::endl;
    }

    void car_book::configure_options(cxxopts::OptionAdder& options_builder)
    {
        add_auth_params(options_builder)
            ("i,id", "Id of the car to book.", cxxopts::value<int>())
            ("s,start",
                "From which date you want to book a car, format dd/mm/yyy: 31/12/2020.",
                cxxopts::value<std::string>())
            ("e,end",
                "Until when you want to book a car, format dd/mm/yyy: 31/12/2020.",
                cxxopts::value<std::string>());
    }

    const crs::console::ROLE car_book::get_permission_level() const
    {
        return crs::console::ROLE::CUSTOMER;
    }
}
