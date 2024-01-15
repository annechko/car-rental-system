#include "car_service.h"

namespace crs::core::service
{
    car_service::car_service()
    {
        car_repository_ = new crs::core::car::car_repository;
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

        return car_repository_->get_list(filters);
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
        car_repository_->delete_car(id);
    }
}