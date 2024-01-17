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
        crs::core::service::car_list_filters* filters = new crs::core::service::car_list_filters();

        std::string start = options["start"].as<std::string>();
        std::string end = options["end"].as<std::string>();

        filters->set_make(options["make"].as<std::string>());
        filters->set_model(options["model"].as<std::string>());
        filters->set_year_from(options["year-from"].as<int>());
        filters->set_year_to(options["year-to"].as<int>());

        filters->set_price_from(options["price-from"].as<float>());
        filters->set_price_to(options["price-to"].as<float>());

        filters->set_sort_field(options["sort"].as<std::string>());
        filters->set_sort_order(options["sort-order"].as<std::string>());

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
                cxxopts::value<std::string>()->default_value(""))
            ("k,make",
                "Company that made a car, for example: Ford, Honda, Volkswagen.",
                cxxopts::value<std::string>()->default_value(""))
            ("o,model",
                "Car's specific name, for example: Escape, Civic, or Jetta.",
                cxxopts::value<std::string>()->default_value(""))
            ("year-from",
                "Show cars with a model year greater than the specified year.",
                cxxopts::value<int>()->default_value("0"))
            ("year-to",
                "Show cars with a model year less than the specified year.",
                cxxopts::value<int>()->default_value("0"))
            ("price-from",
                "Show cars with a price per day greater than the specified year.",
                cxxopts::value<float>()->default_value("0.0"))
            ("price-to",
                "Show cars with a price per day less than the specified year.",
                cxxopts::value<float>()->default_value("0.0"))
            ("sort",
                "Sort cars in a \"sort-order\" (ascending by default) by the field which is one of ["
                    + crs::core::service::car_list_filters::get_allowed_sort_fields_text() + "].",
                cxxopts::value<std::string>()->default_value(""))
            ("sort-order",
                "Sort cars in ascending or descending order, one of [asc|desc]. Requires sort option as well.",
                cxxopts::value<std::string>()->default_value(""));
    }

    const crs::console::ROLE car_list::get_permission_level() const
    {
        return crs::console::ROLE::ANY;
    }
}