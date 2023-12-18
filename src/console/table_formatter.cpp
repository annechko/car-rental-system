#include "table_formatter.h"
#include <tabulate/table.hpp>
#include <ostream>

namespace crs::console
{
    table_formatter::table_formatter()
    {
    }

    void table_formatter::draw_car_list(
        std::vector<std::unique_ptr<crs::core::car::car>>& cars,
        std::ostream& output
    )
    {
        const int HEADER_COUNT = 7;
        using namespace tabulate;
        Table cars_table;
        cars_table.format()
            .column_separator_color(Color::magenta)
            .border_bottom_color(Color::magenta)
            .corner_color(Color::magenta)
            .border_color(Color::magenta);
        cars_table.add_row({
            "ID",
            "Make",
            "Model",
            "Year",
            "Mileage",
            "Min Rent Days",
            "Max Rent Days"
        });

        for (const auto& car : cars)
        {
            cars_table.add_row({
                std::to_string(car->get_id()),
                car->get_make(),
                car->get_model(),
                std::to_string(car->get_year()),
                std::to_string(car->get_mileage()),
                std::to_string(car->get_min_rent()),
                std::to_string(car->get_max_rent()),
            });
        }

        for (short i = 0; i < HEADER_COUNT; ++i)
        {
            cars_table[0][i].format()
                .font_color(Color::green)
                .font_align(FontAlign::left)
                .font_style({ FontStyle::bold });
        }

        output << cars_table << std::endl;
    }
}
