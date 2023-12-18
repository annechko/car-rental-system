#ifndef TABLE_FORMATTER_H
#define TABLE_FORMATTER_H
#include <memory>
#include <vector>
#include "core/car/car.h"

namespace crs::console
{
    class table_formatter
    {
        public:
            table_formatter();
            void draw_car_list(
                std::vector<std::unique_ptr<crs::core::car::car>>& cars,
                std::ostream& output
            );
    };
}

#endif
