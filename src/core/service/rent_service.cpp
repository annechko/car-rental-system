#include "rent_service.h"
#include "core/core_exception.hpp"

namespace crs::core::service
{
    rent_service::rent_service()
    {
        car_repository_ = new crs::core::car::car_repository;
    }

    const float rent_service::calculate(
        int car_id,
        crs::console::date_ymd* start,
        crs::console::date_ymd* end) const
    {
        if (start > end)
        {
            throw core::core_exception("Start date must be before end date.");
        }

        auto car = car_repository_->get_by_id(car_id);
        float day_rent_cost = car->get_day_rent_cost();
        auto diff = std::chrono::sys_days(end->get_ymd()) - std::chrono::sys_days(start->get_ymd());
        int days = diff.count() + 1;

        return float(days * day_rent_cost);
    }
}