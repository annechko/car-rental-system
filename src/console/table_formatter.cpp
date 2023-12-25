#include "table_formatter.h"
#include <ostream>
#include <algorithm>

namespace crs::console
{
    table_formatter::table_formatter()
    {
    }

    void table_formatter::draw_car_list(
        const std::vector<std::unique_ptr<crs::core::car::car>>& cars,
        std::ostream& output
    ) const
    {
        const int COLUMN_COUNT = 8;
        using namespace tabulate;
        Table cars_table;
        Table cars_table_header;
        cars_table_header.add_row({ cars.size() > 0 ? "Car List" : "No cars found." });
        cars_table.add_row({
            "ID",
            "Make",
            "Model",
            "Year",
            "Mileage",
            "Min Rent Days",
            "Max Rent Days",
            "Price for day"
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
                std::to_string(car->get_price_per_day()),
            });
        }

        int max_row_width = calculate_max_row_width(COLUMN_COUNT, cars.size() + 1, cars_table);

        cars_table.format()
            .column_separator_color(Color::magenta)
            .border_bottom_color(Color::magenta)
            .corner_color(Color::magenta)
            .border_color(Color::magenta);
        for (short i = 0; i < COLUMN_COUNT; ++i)
        {
            cars_table[0][i].format()
                .font_color(Color::green)
                .font_align(FontAlign::left)
                .font_style({ FontStyle::bold });
        }

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
            .width(max_row_width + COLUMN_COUNT * 3 - 1);

        output << cars_table_header << std::endl;
        if (cars.size() > 0)
        {
            output << cars_table << std::endl;
        }
    }

    const int table_formatter::calculate_max_row_width(
        short column_count,
        short row_count,
        tabulate::Table table
    ) const
    {
        int max_row_width = 0;
        for (int col = 0; col < column_count; ++col)
        {
            int max_col_width = 0;
            for (int row = 0; row < row_count; ++row)
            {
                max_col_width = std::max(max_col_width, int(table[row][col].size()));
            }
            max_row_width += max_col_width;
        }
        return max_row_width;
    }

    void table_formatter::draw_booking_list(
        const std::vector<std::unique_ptr<crs::core::car::car_booking>>& bookings,
        std::ostream& output
    ) const
    {
        const int COLUMN_COUNT = 6;
        using namespace tabulate;
        Table contents_table;
        Table header;
        header.add_row({ bookings.size() > 0 ? "Car Booking List" : "No bookings found." });
        contents_table.add_row({
            "ID",
            "Car ID",
            "Customer ID",
            "Start",
            "End",
            "Status"
        });

        char date_start[12];
        char date_end[12];
        struct tm ts;
        int booking_row = 1;
        for (const auto& booking : bookings)
        {
            ts = *localtime(new time_t(booking->get_timestamp_start()));
            strftime(date_start, sizeof(date_start), "%Y-%m-%d", &ts);

            ts = *localtime(new time_t(booking->get_timestamp_end()));
            strftime(date_end, sizeof(date_end), "%Y-%m-%d", &ts);

            contents_table.add_row({
                std::to_string(booking->get_id()),
                std::to_string(booking->get_car_id()),
                std::to_string(booking->get_customer_id()),
                date_start,
                date_end,
                booking->get_status_string()
            });
            Color c = Color::grey;
            if (booking->is_new())
            {
                // unapproved booking - yellow color.
                c = Color::yellow;
            }
            else if (booking->is_approved())
            {
                // approved booking - green color.
                c = Color::green;
            }
            else if (booking->is_rejected())
            {
                c = Color::red;
            }
            contents_table[booking_row][5].format()
                .font_style({ FontStyle::bold, FontStyle::italic, })
                .font_color(c);
            booking_row++;
        }


        int max_row_width = calculate_max_row_width(COLUMN_COUNT, bookings.size() + 1, contents_table);

        contents_table.format()
            .column_separator_color(Color::grey)
            .border_bottom_color(Color::grey)
            .corner_color(Color::grey)
            .border_color(Color::grey);
        for (short i = 0; i < COLUMN_COUNT; ++i)
        {
            contents_table[0][i].format()
                .font_align(FontAlign::left)
                .font_style({ FontStyle::bold });
        }

        header.format()
            .border_top(" ")
            .border_bottom(" ")
            .border_left(" ")
            .border_right(" ")
            .corner("★");
        header.format()
            .background_color(Color::green)
            .border_left_color(Color::green)
            .border_left_background_color(Color::green)
            .font_background_color(Color::green)
            .border_right_color(Color::green)
            .border_right_background_color(Color::green)
            .color(Color::grey)
            .font_align(FontAlign::center)
            .font_style({ FontStyle::bold })
            .width(max_row_width + COLUMN_COUNT * 3 - 1);

        output << header << std::endl;
        if (bookings.size() > 0)
        {
            output << contents_table << std::endl;
        }
    }
}
