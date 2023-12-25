#include "date_ymd.h"
#include "core/core_exception.hpp"

namespace crs::core::car
{
    date_ymd::date_ymd(const string& day_month_year)
    {
        struct tm start_result;
        strptime(day_month_year.c_str(), "%d/%m/%Y", &start_result);

        std::chrono::year_month_day date_chrono(
            chrono::year{ 1900 + start_result.tm_year },
            chrono::month(start_result.tm_mon + 1),
            chrono::day(start_result.tm_mday)
        );
        validate(date_chrono);
        ymd_ = date_chrono;
    }

    void date_ymd::validate(const std::chrono::year_month_day& ymd)
    {
        if (!ymd.year().ok() || !((int)ymd.year() >= 2000 && (int)ymd.year() <= 2050))
        {
            throw crs::core::core_exception("Bad year.");
        }
        if (!ymd.month().ok())
        {
            throw core::core_exception("Bad month.");
        }
        if (!ymd.ok() || !ymd.day().ok())
        {
            throw core::core_exception("Bad day.");
        }
    }

    const std::chrono::year_month_day date_ymd::get_ymd() const
    {
        return ymd_;
    }

    std::ostream& operator<<(ostream& ostream, const date_ymd& date)
    {
        int d = unsigned(date.get_ymd().day());
        int m = unsigned(date.get_ymd().month());
        int y = int(date.get_ymd().year());
        ostream << std::to_string(d) + "/" + std::to_string(m) + "/" + std::to_string(y);;
    }

    const int date_ymd::get_timestamp() const
    {
        std::chrono::system_clock::time_point tp_from =
            std::chrono::time_point<std::chrono::system_clock, std::chrono::days>(std::chrono::sys_days{
                get_ymd() });
        const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(tp_from.time_since_epoch());

        return seconds.count();
    }
}
