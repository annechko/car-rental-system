#include "booking_update.h"
#include "core/car/date_ymd.h"
#include "core/core_exception.hpp"
#include <string>

namespace crs::console::command
{
    booking_update::booking_update()
    {
        rent_service_ = new crs::core::service::rent_service;
    }

    const std::string booking_update::get_name() const
    {
        return std::string("booking:update");
    }

    void booking_update::handle(const cxxopts::ParseResult& options, std::ostream& output)
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

        bool approve = options["approve"].as<bool>();
        bool reject = options["reject"].as<bool>();
        if (approve && reject)
        {
            throw crs::core::core_exception("You can not specify these 2 options at the same time.");
        }

        if (approve)
        {
            rent_service_->approve(id);
            output << "Car booking has been approved." << std::endl;
        }
        else if (reject)
        {
            rent_service_->reject(id);
            output << "Car booking has been rejected." << std::endl;
        }
        else
        {
            output << "Nothing was updated, please specify command options." << std::endl;
        }
    }

    void booking_update::configure_options(cxxopts::OptionAdder& options_builder)
    {
        add_auth_params(options_builder)
            ("i,id", "Id of the car booking.", cxxopts::value<int>())
            ("a,approve", "Change status to approved.")
            ("r,reject", "Change status to rejected.");
    }

    const crs::console::ROLE booking_update::get_permission_level() const
    {
        return crs::console::ROLE::ADMIN;
    }
}
