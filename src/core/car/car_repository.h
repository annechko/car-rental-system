#ifndef CAR_REPOSITORY_H
#define CAR_REPOSITORY_H
#include <memory>
#include <vector>
#include "car.h"
#include "core/storage/storage.h"

namespace crs::core::car
{
    class car_repository
    {
        public:
            car_repository();
            void save(car* car_to_add);
            std::vector<std::unique_ptr<car>> get_list();
            car* get_by_id(int id) const;
            void delete_car(int id);
        private:
            crs::core::storage::db* db_;
    };
}

#endif
