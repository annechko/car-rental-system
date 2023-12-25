#ifndef CAR_BOOKING_REPOSITORY_H
#define CAR_BOOKING_REPOSITORY_H
#include <memory>
#include <vector>
#include "car_booking.h"
#include "core/storage/storage.h"
#include "date_ymd.h"

namespace crs::core::car
{
    class car_booking_repository
    {
        public:
            car_booking_repository();
            void save(car_booking* car_booking) const;
            const bool has(int car_id, date_ymd* start, date_ymd* end) const;
            const std::vector<std::unique_ptr<car_booking>> get_list(int user_id) const;
            car_booking* get_by_id(int id) const;
        private:
            crs::core::storage::db* db_;
    };
}

#endif
