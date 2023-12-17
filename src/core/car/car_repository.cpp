#include "car_repository.h"
#include "core/storage/storage.h"
#include "core/core_exception.hpp"
#include <sqlite_orm/sqlite_orm.h>
#include <exception>

namespace crs::core::car
{


    void car_repository::save(car* car_to_add)
    {
        using namespace crs::core;

        auto db = storage::storage::get_instance()->get_db();

        int id = db.insert(*car_to_add);
        car_to_add->set_id(id);
    }

    car_repository::car_repository()
    {

    }
}


