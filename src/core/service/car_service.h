#ifndef CAR_SERVICE_H
#define CAR_SERVICE_H
#include "core/car/car.h"
#include "core/car/car_repository.h"
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
                float day_rent_cost
            ) const;
            crs::core::car::car* update(
                int id,
                const std::string& make,
                const std::string& model,
                int year,
                int mileage,
                int min_rent,
                int max_rent,
                float day_rent_cost
            ) const;
            std::vector<std::unique_ptr<car::car>> get_list() const;
            void delete_car(int id) const;
        private:
            crs::core::car::car_repository* car_repository_;
    };
}
#endif
