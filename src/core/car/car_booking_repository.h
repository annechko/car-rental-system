#ifndef CAR_BOOKING_REPOSITORY_H
#define CAR_BOOKING_REPOSITORY_H
#include <memory>
#include <vector>
#include "car_booking.h"
#include "core/storage/storage.h"
#include "console/date_ymd.h"

namespace crs::core::car
{
    class car_booking_repository
    {
        public:
            car_booking_repository();
            void save(car_booking* car_booking) const;
            const bool has(int car_id, crs::console::date_ymd* start, crs::console::date_ymd* end) const;
            const std::vector<std::unique_ptr<car_booking>> get_list(int user_id) const;
        private:
            crs::core::storage::db* db_;
    };
}

#endif
