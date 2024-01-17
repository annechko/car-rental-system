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

    auto get_order(crs::core::service::car_list_filters* filters, crs::core::storage::db* db_)
    {
        using namespace sqlite_orm;
        using namespace crs::core::service;

        auto order_by_field = dynamic_order_by(*db_);
        bool is_asc = filters->is_sort_asc();
        if (filters->get_sort_field() == car_list_filters::SORT_MODEL)
        {
            auto ord = order_by(&crs::core::car::car::get_model);
            order_by_field.push_back(is_asc ? ord.asc() : ord.desc());
        }
        else if (filters->get_sort_field() == car_list_filters::SORT_MAKE)
        {
            auto ord = order_by(&crs::core::car::car::get_make);
            order_by_field.push_back(is_asc ? ord.asc() : ord.desc());
        }
        else if (filters->get_sort_field() == car_list_filters::SORT_YEAR)
        {
            auto ord = order_by(&crs::core::car::car::get_year);
            order_by_field.push_back(is_asc ? ord.asc() : ord.desc());
        }
        else if (filters->get_sort_field() == car_list_filters::SORT_MIN_RENT)
        {
            auto ord = order_by(&crs::core::car::car::get_min_rent);
            order_by_field.push_back(is_asc ? ord.asc() : ord.desc());
        }
        else if (filters->get_sort_field() == car_list_filters::SORT_MAX_RENT)
        {
            auto ord = order_by(&crs::core::car::car::get_max_rent);
            order_by_field.push_back(is_asc ? ord.asc() : ord.desc());
        }
        else if (filters->get_sort_field() == car_list_filters::SORT_ID)
        {
            auto ord = order_by(&crs::core::car::car::get_id);
            order_by_field.push_back(is_asc ? ord.asc() : ord.desc());
        }
        else if (filters->get_sort_field() == car_list_filters::SORT_PRICE)
        {
            auto ord = order_by(&crs::core::car::car::get_price_per_day);
            order_by_field.push_back(is_asc ? ord.asc() : ord.desc());
        }
        return order_by_field;
    }

    std::vector<std::unique_ptr<car>> car_repository::get_list(
        crs::core::service::car_list_filters* filters,
        std::vector<int> car_ids_with_bookings_for_same_period
    )
    {
        int days = filters->get_days_amount();
        using namespace sqlite_orm;

        auto order_by_field = get_order(filters, db_);

        return db_->get_all_pointer<crs::core::car::car>(
            where(
                not_in(&crs::core::car::car::get_id, car_ids_with_bookings_for_same_period) and
                    (days <= 0 or (
                        (
                            c(&crs::core::car::car::get_min_rent) <= days
                                and c(&crs::core::car::car::get_max_rent) >= days
                        )
                            or (
                                (c(&crs::core::car::car::get_min_rent) == 0)
                                    and c(&crs::core::car::car::get_max_rent) == 0
                            )
                            or (
                                c(&crs::core::car::car::get_min_rent) <= days
                                    and c(&crs::core::car::car::get_max_rent) == 0
                            )
                            or (
                                c(&crs::core::car::car::get_max_rent) >= days
                                    and (c(&crs::core::car::car::get_min_rent) == 0)
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
            ),
            order_by_field
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


