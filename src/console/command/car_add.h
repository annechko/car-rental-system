#ifndef CAR_ADD_H
#define CAR_ADD_H
#include "abstract_command.h"
#include <core/service/auth_service.h>

namespace crs::console::command
{
    class car_add : public abstract_command
    {
        public:
            car_add();
            const std::string get_name() const override;
            void handle(cxxopts::ParseResult& result, std::stringstream& output) override;
            void configure_options(cxxopts::OptionAdder& options) override;
            const crs::console::ROLE get_permission_level() const override;
    };

}


#endif
