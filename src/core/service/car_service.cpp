#include "car_service.h"
#include <vector>
#include "core/core_exception.hpp"

namespace crs::core::service
{
    car_service::car_service()
    {
        car_repository_ = new crs::core::car::car_repository;
        car_booking_repository_ = new crs::core::car::car_booking_repository;
    }

    crs::core::car::car* car_service::create(
        const std::string& make,
        const std::string& model,
        int year,
        int mileage,
        int min_rent,
        int max_rent,
        float price_per_day
    ) const
    {
        auto car = new car::car(make, model, year, mileage, min_rent, max_rent, price_per_day);
        car_repository_->save(car);
        return car;
    }

    std::vector<std::unique_ptr<car::car>> car_service::get_list(car_list_filters* filters) const
    {
        filters->validate();

        std::vector<int> car_ids_with_bookings_for_same_period;

        if (filters->has_period())
        {
            car_ids_with_bookings_for_same_period = car_booking_repository_->get_car_ids_with_bookings(
                filters->get_start_ymd(),
                filters->get_end_ymd()
            );
        }
        else
        {
            car_ids_with_bookings_for_same_period.push_back(-1);
        }


        return car_repository_->get_list(filters, car_ids_with_bookings_for_same_period);
    }

    crs::core::car::car* car_service::update(
        int id,
        const std::string& make,
        const std::string& model,
        int year,
        int mileage,
        int min_rent,
        int max_rent,
        float price_per_day
    ) const
    {
        auto car = car_repository_->get_by_id(id);
        car->update(make, model, year, mileage, min_rent, max_rent, price_per_day);
        car_repository_->save(car);
        return car;
    }

    void car_service::delete_car(int id) const
    {
        // check car exists.
        auto car = car_repository_->get_by_id(id);

        // check bookings exist.
        if (car_booking_repository_->has_by_car_id(id))
        {
            throw core::core_exception("Car with id = " + std::to_string(id)
                + " cannot be deleted because of the bookings of this car.");
        }

        car_repository_->delete_car(id);
    }
}