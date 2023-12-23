#ifndef RENT_SERVICE_H
#define RENT_SERVICE_H

#include <ctime>
#include "console/date_ymd.h"
#include "core/car/car_repository.h"
#include "core/car/car_booking_repository.h"

namespace crs::core::service
{
    class rent_service
    {
        public:
            rent_service();
            const float calculate(
                int car_id,
                crs::console::date_ymd* start,
                crs::console::date_ymd* end
            ) const;
            void book(
                int customer_id,
                int car_id,
                crs::console::date_ymd* start,
                crs::console::date_ymd* end
            ) const;
        private:
            const float calculate(
                float price_per_day,
                crs::console::date_ymd* start,
                crs::console::date_ymd* end) const;
            const crs::core::car::car_repository* car_repository_;
            const crs::core::car::car_booking_repository* car_booking_repository_;
    };

}

#endif
