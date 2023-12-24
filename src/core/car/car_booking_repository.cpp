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

    const bool car_booking_repository::has(
        int car_id,
        crs::console::date_ymd* start,
        crs::console::date_ymd* end
    ) const
    {
        using namespace sqlite_orm;
        auto other_bookings = db_->select(
            &crs::core::car::car_booking::get_id,
            where(c(&crs::core::car::car_booking::get_car_id) == car_id
                and (
                    (c(&crs::core::car::car_booking::get_timestamp_start) <= end->get_timestamp())
                        and (c(&crs::core::car::car_booking::get_timestamp_end) >= start->get_timestamp())
                )
            ),
            limit(1)
        );

        return other_bookings.size() > 0;
    }

    const std::vector<std::unique_ptr<car_booking>> car_booking_repository::get_list() const
    {
        return db_->get_all_pointer<car_booking>();
    }
}


