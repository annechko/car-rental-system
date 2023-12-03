#include "user_repository.h"
#include "core/storage/storage.h"
#include "core/validation_exception.h"

crs::core::user::user crs::core::user::user_repository::get_by_id(int id)
{
    using namespace crs::core;

    auto db = core::storage::storage::get_instance()->get_db();
    auto user_data = db.get_pointer<core::storage::user_data>(id);
    if (user_data)
    {
        return user(user_data->name);
    }
    else
    {
        throw core::validation_exception("no user with id ");
    }
}
void crs::core::user::user_repository::save(crs::core::user::user user_to_add)
{

}

