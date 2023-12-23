#ifndef RENT_SERVICE_H
#define RENT_SERVICE_H

#include <ctime>
#include "console/date_ymd.h"
#include "core/car/car_repository.h"

namespace crs::core::service
{
    class rent_service
    {
        public:
            rent_service();
            const float calculate(
                int car_id,
                crs::console::date_ymd* from,
                crs::console::date_ymd* to
            ) const;
        private:
            const crs::core::car::car_repository* car_repository_;
    };

}

#endif
