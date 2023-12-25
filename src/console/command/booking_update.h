#ifndef BOOKING_UPDATE_H
#define BOOKING_UPDATE_H

#include "abstract_command.h"
#include "core/service/rent_service.h"

namespace crs::console::command
{
    class booking_update : public abstract_command
    {
        public:
            booking_update();
            const std::string get_name() const override;
            void handle(const cxxopts::ParseResult& options, std::ostream& output) override;
            void configure_options(cxxopts::OptionAdder& options) override;
            const crs::console::ROLE get_permission_level() const override;

        private:
            const crs::core::service::rent_service* rent_service_;
    };
}

#endif
