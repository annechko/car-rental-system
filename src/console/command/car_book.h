#ifndef CAR_BOOK_H
#define CAR_BOOK_H
#include "abstract_command.h"
#include "core/service/rent_service.h"

namespace crs::console::command
{
    class car_book : public abstract_command
    {
        public:
            car_book();
            const std::string get_name() const override;
            void handle(cxxopts::ParseResult& options, std::ostream& output) override;
            void configure_options(cxxopts::OptionAdder& options) override;
            const crs::console::ROLE get_permission_level() const override;

        private:
            const crs::core::service::rent_service* rent_service_;
    };
}

#endif
