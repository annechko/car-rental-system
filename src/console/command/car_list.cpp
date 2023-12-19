#include "car_list.h"
#include "core/car/car.h"
#include "core/storage/storage.h"

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

    void car_list::handle(cxxopts::ParseResult& options, std::ostream& output)
    {
        auto cars = car_service_->get_list();
        table_formatter_->draw_car_list(cars, output);
    }

    void car_list::configure_options(cxxopts::OptionAdder& options_builder)
    {

    }

    const crs::console::ROLE car_list::get_permission_level() const
    {
        return crs::console::ROLE::ANY;
    }
}