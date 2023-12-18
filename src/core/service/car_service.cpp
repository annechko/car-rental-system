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
        int max_rent) const
    {
        auto car = new car::car(make, model, year, mileage, min_rent, max_rent);
        car_repository_->save(car);
        return car;
    }

    std::vector<std::unique_ptr<car::car>> car_service::get_list() const
    {
        return car_repository_->get_list();
    }
}