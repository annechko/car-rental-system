#ifndef BOOKING_LIST_H
#define BOOKING_LIST_H
#include "abstract_command.h"
#include "core/service/rent_service.h"
#include "console/table_formatter.h"

namespace crs::console::command
{
    class booking_list : public abstract_command
    {
        public:
            booking_list();
            const std::string get_name() const override;
            void handle(const cxxopts::ParseResult& options, std::ostream& output) override;
            void configure_options(cxxopts::OptionAdder& options) override;
            const crs::console::ROLE get_permission_level() const override;
        private:
            const crs::core::service::rent_service* rent_service_;
            const crs::console::table_formatter* table_formatter_;
    };
}

#endif
