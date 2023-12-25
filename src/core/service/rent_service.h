#ifndef RENT_SERVICE_H
#define RENT_SERVICE_H
#include <ctime>
#include "core/car/date_ymd.h"
#include "core/car/car_repository.h"
#include "core/car/car_booking_repository.h"
#include <memory>
#include <vector>

namespace crs::core::service
{
    class rent_service
    {
        public:
            rent_service();
            const float calculate(
                int car_id,
                crs::core::car::date_ymd* start,
                crs::core::car::date_ymd* end
            ) const;
            float book(
                int customer_id,
                int car_id,
                crs::core::car::date_ymd* start,
                crs::core::car::date_ymd* end
            ) const;
            const std::vector<std::unique_ptr<crs::core::car::car_booking>> get_list(int user_id) const;
        private:
            const float calculate(
                crs::core::car::car* car,
                crs::core::car::date_ymd* start,
                crs::core::car::date_ymd* end
            ) const;
            const crs::core::car::car_repository* car_repository_;
            const crs::core::car::car_booking_repository* car_booking_repository_;
    };

}

#endif
