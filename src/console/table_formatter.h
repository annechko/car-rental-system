#ifndef TABLE_FORMATTER_H
#define TABLE_FORMATTER_H
#include <memory>
#include <vector>
#include "core/car/car.h"
#include "core/car/car_booking.h"
#include <tabulate/table.hpp>

namespace crs::console
{
    class table_formatter
    {
        public:
            table_formatter();
            void draw_car_list(
                const std::vector<std::unique_ptr<crs::core::car::car>>& cars,
                std::ostream& output
            ) const;
            void draw_booking_list(
                const std::vector<std::unique_ptr<crs::core::car::car_booking>>& bookings,
                std::ostream& ostream
            ) const;

        private:
            const int calculate_max_row_width(
                short column_count,
                short row_count,
                tabulate::Table table
            ) const;
    };
}

#endif
