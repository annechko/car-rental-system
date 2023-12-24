#include "rent_service.h"
#include "core/core_exception.hpp"
#include "core/car/car_booking.h"
#include <chrono>
#include <iostream>

namespace crs::core::service
{
    rent_service::rent_service()
    {
        car_repository_ = new crs::core::car::car_repository;
        car_booking_repository_ = new crs::core::car::car_booking_repository;
    }

    const float rent_service::calculate(
        crs::core::car::car* car,
        crs::console::date_ymd* start,
        crs::console::date_ymd* end
    ) const
    {
        if (start->get_timestamp() > end->get_timestamp())
        {
            throw core::core_exception("Start date must be before end date.");
        }
        if (car_booking_repository_->has(car->get_id(), start, end))
        {
            throw core::core_exception("Car is unavailable for these dates.");
        }
        // todo check min/max rent

        auto diff = std::chrono::sys_days(end->get_ymd()) - std::chrono::sys_days(start->get_ymd());
        int days = diff.count() + 1;
        auto price_per_day = car->get_price_per_day();

        return float(days * price_per_day);
    }

    const float rent_service::calculate(
        int car_id,
        crs::console::date_ymd* start,
        crs::console::date_ymd* end
    ) const
    {
        auto car = car_repository_->get_by_id(car_id);

        return calculate(car, start, end);
    }

    float rent_service::book(
        int customer_id,
        int car_id,
        crs::console::date_ymd* start,
        crs::console::date_ymd* end) const
    {
        auto car = car_repository_->get_by_id(car_id);

        float total_price = calculate(car, start, end);
        auto car_booking = new crs::core::car::car_booking(
            customer_id,
            car_id,
            total_price,
            start->get_timestamp(),
            end->get_timestamp()
        );
        car_booking_repository_->save(car_booking);

        return total_price;
    }

    const std::vector<std::unique_ptr<crs::core::car::car_booking>> rent_service::get_list() const
    {
        return car_booking_repository_->get_list();
    }
}