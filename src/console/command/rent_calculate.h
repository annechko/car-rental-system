#ifndef RENT_CALCULATE_H
#define RENT_CALCULATE_H
#include "abstract_command.h"
#include "core/service/rent_service.h"

namespace crs::console::command
{
    class rent_calculate : public abstract_command
    {
        public:
            rent_calculate();
            const std::string get_name() const override;
            void handle(const cxxopts::ParseResult& options, std::ostream& output) override;
            void configure_options(cxxopts::OptionAdder& options) override;
            const crs::console::ROLE get_permission_level() const override;

        private:
            const crs::core::service::rent_service* rent_service_;
    };
}

#endif
