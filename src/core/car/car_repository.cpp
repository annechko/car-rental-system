#include "car_repository.h"
#include "core/storage/storage.h"
#include "core/core_exception.hpp"
#include <sqlite_orm/sqlite_orm.h>
#include <memory>

namespace crs::core::car
{
    car_repository::car_repository()
    {
        db_ = storage::storage::get_instance()->get_db();
    }

    void car_repository::save(crs::core::car::car* car)
    {
        using namespace crs::core;
        if (car->get_id() <= 0)
        {
            int id = db_->insert(*car);
            car->set_id(id);
        }
        else
        {
            db_->update(*car);
        }
    }

    std::vector<std::unique_ptr<car>> car_repository::get_list(crs::core::service::car_list_filters* filters)
    {
        int days = filters->get_days_amount();

        using namespace sqlite_orm;

        return db_->get_all_pointer<crs::core::car::car>(
            where(
                c(&crs::core::car::car::get_id) > 0 and
                    (days <= 0 or (
                        (
                            c(&crs::core::car::car::get_min_rent) <= days
                                and c(&crs::core::car::car::get_max_rent) >= days
                        )
                            or (
                                (c(&crs::core::car::car::get_min_rent) == 0)
                                    and c(&crs::core::car::car::get_max_rent) == 0
                            )
                    ))
                    and
                        (filters->get_model().empty()
                            or c(&crs::core::car::car::get_model) == filters->get_model())
                    and
                        (filters->get_make().empty()
                            or c(&crs::core::car::car::get_make) == filters->get_make())
                    and
                        (filters->get_year_from() <= 0
                            or c(&crs::core::car::car::get_year) >= filters->get_year_from())
                    and
                        (filters->get_year_to() <= 0
                            or c(&crs::core::car::car::get_year) <= filters->get_year_to())
                    and
                        (filters->get_price_from() <= 0
                            or c(&crs::core::car::car::get_price_per_day) >= filters->get_price_from())
                    and
                        (filters->get_price_to() <= 0
                            or c(&crs::core::car::car::get_price_per_day) <= filters->get_price_to())
            )
        );
    }

    car* car_repository::get_by_id(int id) const
    {
        using namespace crs::core;

        auto result = db_->get_pointer<car>(id);
        if (result)
        {
            return result.release();
        }
        else
        {
            throw core::core_exception("Car with id = " + std::to_string(id) + " not found.");
        }
    }

    void car_repository::delete_car(int id)
    {
        db_->remove<car>(id);
    }
}


