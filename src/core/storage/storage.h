#ifndef STORAGE_H
#define STORAGE_H
#include <sqlite_orm/sqlite_orm.h>
#include "core/user/user.h"
#include "core/car/car.h"
#include "core/car/car_booking.h"

namespace crs::core::storage
{
    inline auto init_storage(const std::string& path)
    {
        using namespace sqlite_orm;
        return make_storage(path,
            make_table("user",
                make_column("id",
                    &crs::core::user::user::set_id,
                    &crs::core::user::user::get_id,
                    primary_key()),
                make_column("name",
                    &crs::core::user::user::set_name,
                    &crs::core::user::user::get_name,
                    unique()),
                make_column("password_hash",
                    &crs::core::user::user::set_password_hash,
                    &crs::core::user::user::get_password_hash),
                make_column("role",
                    &crs::core::user::user::set_role_value,
                    &crs::core::user::user::get_role_value)
            ),
            make_table("car",
                make_column("id",
                    &crs::core::car::car::set_id,
                    &crs::core::car::car::get_id,
                    primary_key()),
                make_column("make",
                    &crs::core::car::car::set_make,
                    &crs::core::car::car::get_make),
                make_column("model",
                    &crs::core::car::car::set_model,
                    &crs::core::car::car::get_model),
                make_column("year",
                    &crs::core::car::car::set_year,
                    &crs::core::car::car::get_year),
                make_column("mileage",
                    &crs::core::car::car::set_mileage,
                    &crs::core::car::car::get_mileage),
                make_column("min_rent",
                    &crs::core::car::car::set_min_rent,
                    &crs::core::car::car::get_min_rent),
                make_column("max_rent",
                    &crs::core::car::car::set_max_rent,
                    &crs::core::car::car::get_max_rent),
                make_column("price_per_day",
                    &crs::core::car::car::set_price_per_day,
                    &crs::core::car::car::get_price_per_day)
            ),
            make_table("car_booking",
                make_column("id",
                    &crs::core::car::car_booking::set_id,
                    &crs::core::car::car_booking::get_id,
                    primary_key()),
                make_column("car_id",
                    &crs::core::car::car_booking::set_car_id,
                    &crs::core::car::car_booking::get_car_id),
                make_column("customer_id",
                    &crs::core::car::car_booking::set_customer_id,
                    &crs::core::car::car_booking::get_customer_id),
                make_column("total_price",
                    &crs::core::car::car_booking::set_price,
                    &crs::core::car::car_booking::get_price),
                make_column("timestamp_start",
                    &crs::core::car::car_booking::set_timestamp_start,
                    &crs::core::car::car_booking::get_timestamp_start),
                make_column("timestamp_end",
                    &crs::core::car::car_booking::set_timestamp_end,
                    &crs::core::car::car_booking::get_timestamp_end)
            )
        );
    }

    using db = decltype(init_storage(""));

    class storage
    {
        public:
            storage(storage& other) = delete;
            void operator=(const storage&) = delete;
            static storage* get_instance();

            db* get_db();
        private:
            static storage* instance_;
            db* db_;
            storage();
    };
}

#endif
