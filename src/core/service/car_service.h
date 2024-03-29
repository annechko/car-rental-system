#ifndef CAR_SERVICE_H
#define CAR_SERVICE_H
#include "core/car/car.h"
#include "core/car/car_repository.h"
#include "car_list_filters.h"
#include "core/car/car_booking_repository.h"
#include <memory>
#include <vector>

namespace crs::core::service
{
    class car_service
    {
        public:
            car_service();
            crs::core::car::car* create(
                const std::string& make,
                const std::string& model,
                int year,
                int mileage,
                int min_rent,
                int max_rent,
                float price_per_day
            ) const;
            crs::core::car::car* update(
                int id,
                const std::string& make,
                const std::string& model,
                int year,
                int mileage,
                int min_rent,
                int max_rent,
                float price_per_day
            ) const;
            std::vector<std::unique_ptr<car::car>> get_list(car_list_filters* filters) const;
            void delete_car(int id) const;
        private:
            crs::core::car::car_repository* car_repository_;
            crs::core::car::car_booking_repository* car_booking_repository_;
    };
}
#endif
