#include "date_ymd.h"
#include "core/core_exception.hpp"

namespace crs::console
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

    void date_ymd::print(ostream& ostream) const
    {
        int d = unsigned(get_ymd().day());
        int m = unsigned(get_ymd().month());
        int y = int(get_ymd().year());
        ostream << std::to_string(d) << '/' << m << '/' << y;
    }
}
