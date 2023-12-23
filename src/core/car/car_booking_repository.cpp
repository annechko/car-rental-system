#include "car_booking_repository.h"
#include "core/storage/storage.h"

namespace crs::core::car
{
    car_booking_repository::car_booking_repository()
    {
        db_ = storage::storage::get_instance()->get_db();
    }

    void car_booking_repository::save(crs::core::car::car_booking* car_booking) const
    {
        using namespace crs::core;
        if (car_booking->get_id() <= 0)
        {
            int id = db_->insert(*car_booking);
            car_booking->set_id(id);
        }
        else
        {
            db_->update(*car_booking);
        }
    }
}


