#ifndef CAR_DELETE_H
#define CAR_DELETE_H
#include "abstract_command.h"
#include "core/service/car_service.h"

namespace crs::console::command
{
    class car_delete : public abstract_command
    {
        public:
            car_delete();
            const std::string get_name() const override;
            void handle(const cxxopts::ParseResult& options, std::ostream& output) override;
            void configure_options(cxxopts::OptionAdder& options) override;
            const crs::console::ROLE get_permission_level() const override;

        private:
            const crs::core::service::car_service* car_service_;
    };
}

#endif
