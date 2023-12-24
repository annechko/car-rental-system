#include "booking_list.h"
#include <ostream>

namespace crs::console::command
{
    booking_list::booking_list()
    {
        rent_service_ = new crs::core::service::rent_service;
        table_formatter_ = new crs::console::table_formatter;
    }

    const std::string booking_list::get_name() const
    {
        return std::string("booking:list");
    }

    void booking_list::handle(cxxopts::ParseResult& options, std::ostream& output)
    {
        authenticate_if_needed(options);

        auto booking_list = rent_service_->get_list();
        table_formatter_->draw_booking_list(booking_list, output);
    }

    void booking_list::configure_options(cxxopts::OptionAdder& options_builder)
    {
        add_auth_params(options_builder);
    }

    const crs::console::ROLE booking_list::get_permission_level() const
    {
        return crs::console::ROLE::AUTHENTICATED;
    }
}