#include "car_list.h"
#include "core/car/car.h"
#include "core/storage/storage.h"
#include "core/service/car_list_filters.h"
#include "core/core_exception.hpp"
#include "core/car/date_ymd.h"

namespace crs::console::command
{
    car_list::car_list()
    {
        car_service_ = new crs::core::service::car_service;
        table_formatter_ = new crs::console::table_formatter;
    }

    const std::string car_list::get_name() const
    {
        return std::string("car:list");
    }

    void car_list::handle(const cxxopts::ParseResult& options, std::ostream& output)
    {
        std::string start = options["start"].as<std::string>();
        std::string end = options["end"].as<std::string>();

        crs::core::service::car_list_filters* filters = new crs::core::service::car_list_filters();

        if (!start.empty())
        {
            try
            {
                filters->set_start_ymd(new crs::core::car::date_ymd(start));
            }
            catch (const core::core_exception& exception)
            {
                throw core::core_exception("Start date: " + std::string(exception.what()));
            }
        }
        if (!end.empty())
        {
            try
            {
                filters->set_end_ymd(new crs::core::car::date_ymd(end));
            }
            catch (const core::core_exception& exception)
            {
                throw core::core_exception("End date: " + std::string(exception.what()));
            }
        }


        auto cars = car_service_->get_list(filters);
        table_formatter_->draw_car_list(cars, output);
    }

    void car_list::configure_options(cxxopts::OptionAdder& options_builder)
    {
        options_builder
            ("start",
                "start which date you want to book a car, format dd/mm/yyy: 31/12/2020.",
                cxxopts::value<std::string>()->default_value(""))
            ("end",
                "Until when you want to book a car, format dd/mm/yyy: 31/12/2020.",
                cxxopts::value<std::string>()->default_value(""));
    }

    const crs::console::ROLE car_list::get_permission_level() const
    {
        return crs::console::ROLE::ANY;
    }
}