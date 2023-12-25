#include "booking_add.h"
#include "core/car/date_ymd.h"
#include "core/core_exception.hpp"
#include <string>

namespace crs::console::command
{
    booking_add::booking_add()
    {
        rent_service_ = new crs::core::service::rent_service;
    }

    const std::string booking_add::get_name() const
    {
        return std::string("booking:add");
    }

    void booking_add::handle(const cxxopts::ParseResult& options, std::ostream& output)
    {
        authenticate(options);

        int id = options["id"].as<int>();
        if (id <= 0)
        {
            throw crs::core::core_exception("Id must be greater than 0.");
        }
        if (user_ == nullptr)
        {
            throw crs::core::core_exception("User Id must be greater than 0.");
        }
        std::string start = options["start"].as<std::string>();
        std::string end = options["end"].as<std::string>();

        crs::core::car::date_ymd* start_ymd;
        crs::core::car::date_ymd* end_ymd;
        try
        {
            start_ymd = new crs::core::car::date_ymd(start);
        }
        catch (const core::core_exception& exception)
        {
            throw core::core_exception("Start date: " + std::string(exception.what()));
        }
        try
        {
            end_ymd = new crs::core::car::date_ymd(end);
        }
        catch (const core::core_exception& exception)
        {
            throw core::core_exception("End date: " + std::string(exception.what()));
        }

        auto total = rent_service_->book(user_->get_id(), id, start_ymd, end_ymd);

        output << "Car has successfully been booked, the payment will be " << total << " NZD." << std::endl;
    }

    void booking_add::configure_options(cxxopts::OptionAdder& options_builder)
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

    const crs::console::ROLE booking_add::get_permission_level() const
    {
        return crs::console::ROLE::CUSTOMER;
    }
}
