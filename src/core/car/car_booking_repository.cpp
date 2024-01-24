#include "car_booking_repository.h"
#include "core/storage/storage.h"
#include "date_ymd.h"
#include "core/core_exception.hpp"
#include "core/car/car_booking.h"

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
        date_ymd* start,
        date_ymd* end
    ) const
    {
        using namespace sqlite_orm;
        auto other_bookings = db_->select(
            &crs::core::car::car_booking::get_id,
            where(c(&crs::core::car::car_booking::get_car_id) == car_id
                and c(&crs::core::car::car_booking::get_status)
                    != crs::core::car::car_booking::get_rejected_status_value()
                and (
                    (c(&crs::core::car::car_booking::get_timestamp_start) <= end->get_timestamp())
                        and (c(&crs::core::car::car_booking::get_timestamp_end) >= start->get_timestamp())
                )
            ),
            limit(1)
        );

        return other_bookings.size() > 0;
    }

    const std::vector<std::unique_ptr<car_booking>> car_booking_repository::get_list(int user_id = 0) const
    {
        if (user_id > 0)
        {
            using namespace sqlite_orm;

            return db_->get_all_pointer<car_booking>(
                where(c(&crs::core::car::car_booking::get_customer_id) == user_id)
            );
        }
        return db_->get_all_pointer<car_booking>();
    }

    car_booking* car_booking_repository::get_by_id(int id) const
    {
        using namespace crs::core;

        auto result = db_->get_pointer<car_booking>(id);
        if (result)
        {
            return result.release();
        }
        else
        {
            throw core::core_exception("Car booking with id = " + std::to_string(id) + " not found.");
        }
    }

    const std::vector<int> car_booking_repository::get_car_ids_with_bookings(
        date_ymd* start,
        date_ymd* end
    ) const
    {
        using namespace sqlite_orm;

        return db_->select(
            &crs::core::car::car_booking::get_car_id,
            where(
                c(&crs::core::car::car_booking::get_timestamp_start) <= end->get_timestamp()
                    and c(&crs::core::car::car_booking::get_timestamp_end) >= start->get_timestamp()
                    and c(&crs::core::car::car_booking::get_status)
                        != crs::core::car::car_booking::get_rejected_status_value()
            )
        );
    }

    const bool car_booking_repository::has_by_car_id(int car_id) const
    {
        using namespace sqlite_orm;
        auto bookings = db_->select(
            &crs::core::car::car_booking::get_id,
            where(c(&crs::core::car::car_booking::get_car_id) == car_id),
            limit(1)
        );

        return bookings.size() > 0;
    }
}


