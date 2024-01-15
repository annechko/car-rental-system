#ifndef CAR_LIST_FILTERS_H
#define CAR_LIST_FILTERS_H
#include "core/car/date_ymd.h"

namespace crs::core::service
{
    class car_list_filters
    {
        public:
            car_list_filters();
            void validate();
            car::date_ymd* get_start_ymd() const;
            void set_start_ymd(car::date_ymd* start_ymd);
            car::date_ymd* get_end_ymd() const;
            void set_end_ymd(car::date_ymd* end_ymd);
            const int get_days_amount() const;
        private:
            crs::core::car::date_ymd* start_ymd_ = nullptr;
            crs::core::car::date_ymd* end_ymd_ = nullptr;
    };

}

#endif
