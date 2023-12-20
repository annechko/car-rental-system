#include "table_formatter.h"
#include <tabulate/table.hpp>
#include <ostream>
#include <algorithm>

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
        const int COLUMN_COUNT = 7;
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

        int max_row_width = 0;
        for (int col = 0; col < COLUMN_COUNT; ++col)
        {
            int max_col_width = 0;
            for (int row = 0; row < cars.size(); ++row)
            {
                max_col_width = std::max(max_col_width, int(cars_table[row][col].size()));
            }
            max_row_width += max_col_width;
        }

        for (short i = 0; i < COLUMN_COUNT; ++i)
        {
            cars_table[0][i].format()
                .font_color(Color::green)
                .font_align(FontAlign::left)
                .font_style({ FontStyle::bold });
        }

        Table cars_table_header;
        cars_table_header.add_row({ "Car List" });
        cars_table_header.format()
            .border_top(" ")
            .border_bottom(" ")
            .border_left(" ")
            .border_right(" ")
            .corner(" ");
        cars_table_header.column(0).format()
            .background_color(Color::magenta)
            .border_left_color(Color::magenta)
            .border_left_background_color(Color::magenta)
            .font_background_color(Color::magenta)
            .font_color(Color::magenta)
            .border_right_color(Color::magenta)
            .border_right_background_color(Color::magenta)
            .color(Color::yellow)
            .font_align(FontAlign::center)
            .font_style({ FontStyle::bold })
            .width(max_row_width + COLUMN_COUNT * 3 + 7);

        output << cars_table_header << std::endl;
        output << cars_table << std::endl;
    }
}
