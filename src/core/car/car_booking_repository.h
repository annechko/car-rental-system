#ifndef CAR_BOOKING_REPOSITORY_H
#define CAR_BOOKING_REPOSITORY_H
#include <memory>
#include <vector>
#include "car_booking.h"
#include "core/storage/storage.h"

namespace crs::core::car
{
    class car_booking_repository
    {
        public:
            car_booking_repository();
            void save(car_booking* car_booking) const;
        private:
            crs::core::storage::db* db_;
    };
}

#endif
