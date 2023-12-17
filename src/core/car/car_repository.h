#ifndef CAR_REPOSITORY_H
#define CAR_REPOSITORY_H
#include "car.h"

namespace crs::core::car
{
    class car_repository
    {
        public:
            car_repository();
            void save(car* car_to_add);
    };
}

#endif
