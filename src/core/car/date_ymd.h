#ifndef DATE_YMD_H
#define DATE_YMD_H
#include <chrono>
#include <string>
#include <iostream>
#include <string>

namespace crs::core::car
{
    class date_ymd
    {
        public:
            date_ymd(const std::string& day_month_year);
            const std::chrono::year_month_day get_ymd() const;
            const int get_timestamp() const;
            friend std::ostream& operator<<(std::ostream& ostream, date_ymd const& date);
            const int count_days_till(date_ymd* pYmd) const;
        private:
            std::chrono::year_month_day ymd_;
            void validate(const std::chrono::year_month_day& ymd);
    };

}
#endif
