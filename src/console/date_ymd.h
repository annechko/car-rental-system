#ifndef DATE_YMD_H
#define DATE_YMD_H
#include <chrono>
#include <string>
#include <iostream>

namespace crs::console
{
    class date_ymd
    {
        public:
            date_ymd(const std::string& day_month_year);
            const std::chrono::year_month_day get_ymd() const;
            void print(std::ostream& ostream) const;
        private:
            std::chrono::year_month_day ymd_;
            void validate(const std::chrono::year_month_day& ymd);
    };

}
#endif
