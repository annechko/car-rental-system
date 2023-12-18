#include "car_repository.h"
#include "core/storage/storage.h"
#include <sqlite_orm/sqlite_orm.h>

namespace crs::core::car
{
    car_repository::car_repository()
    {
        db_ = storage::storage::get_instance()->get_db();
    }

    void car_repository::save(crs::core::car::car* car_to_add)
    {
        using namespace crs::core;
        int id = db_->insert(*car_to_add);
        car_to_add->set_id(id);
    }

    std::vector<std::unique_ptr<crs::core::car::car>> car_repository::get_list()
    {
        return std::vector<std::unique_ptr<crs::core::car::car>>();
    }
}


