#include "car_list_filters.h"
#include "core/core_exception.hpp"

namespace crs::core::service
{
    car_list_filters::car_list_filters()
    {
    }

    void car_list_filters::validate()
    {
        if ((start_ymd_ != nullptr && end_ymd_ == nullptr)
            || (start_ymd_ == nullptr && end_ymd_ != nullptr))
        {
            throw core::core_exception("Both start and end are required to specify a period.");
        }
    }

    car::date_ymd* car_list_filters::get_start_ymd() const
    {
        return start_ymd_;
    }

    void car_list_filters::set_start_ymd(car::date_ymd* start_ymd)
    {
        start_ymd_ = start_ymd;
    }

    car::date_ymd* car_list_filters::get_end_ymd() const
    {
        return end_ymd_;
    }

    void car_list_filters::set_end_ymd(car::date_ymd* end_ymd)
    {
        end_ymd_ = end_ymd;
    }

    const int car_list_filters::get_days_amount() const
    {
        if (start_ymd_ == nullptr || end_ymd_ == nullptr)
        {
            return -1;
        }

        return get_start_ymd()->count_days_till(get_end_ymd());
    }
}
