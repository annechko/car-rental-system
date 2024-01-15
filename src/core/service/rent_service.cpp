#include "rent_service.h"
#include "core/core_exception.hpp"
#include "core/car/car_booking.h"
#include <chrono>

namespace crs::core::service
{
    rent_service::rent_service()
    {
        car_repository_ = new crs::core::car::car_repository;
        car_booking_repository_ = new crs::core::car::car_booking_repository;
    }

    const float rent_service::calculate(
        crs::core::car::car* car,
        crs::core::car::date_ymd* start,
        crs::core::car::date_ymd* end
    ) const
    {
        if (car_booking_repository_->has(car->get_id(), start, end))
        {
            throw core::core_exception("Car is unavailable for these dates.");
        }

        int days = start->count_days_till(end);
        int min_days = car->get_min_rent();
        int max_days = car->get_max_rent();
        if (!car->can_be_rented_for_days(days))
        {
            throw core::core_exception(
                "Car cannot be rented for " + std::to_string(days)
                    + " days, only from " + std::to_string(min_days)
                    + " days to " + std::to_string(max_days) + " days."
            );
        }
        auto price_per_day = car->get_price_per_day();

        return float(days * price_per_day);
    }

    const float rent_service::calculate(
        int car_id,
        crs::core::car::date_ymd* start,
        crs::core::car::date_ymd* end
    ) const
    {
        auto car = car_repository_->get_by_id(car_id);

        return calculate(car, start, end);
    }

    float rent_service::book(
        int customer_id,
        int car_id,
        crs::core::car::date_ymd* start,
        crs::core::car::date_ymd* end) const
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

    const std::vector<std::unique_ptr<crs::core::car::car_booking>> rent_service::get_list(
        int user_id = 0
    ) const
    {
        return car_booking_repository_->get_list(user_id);
    }

    void rent_service::approve(int booking_id) const
    {
        auto car_booking = car_booking_repository_->get_by_id(booking_id);
        car_booking->approve();
        car_booking_repository_->save(car_booking);
    }

    void rent_service::reject(int booking_id) const
    {
        auto car_booking = car_booking_repository_->get_by_id(booking_id);
        car_booking->reject();
        car_booking_repository_->save(car_booking);
    }
}