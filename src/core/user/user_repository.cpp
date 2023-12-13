#include "user_repository.h"
#include "core/storage/storage.h"
#include "core/core_exception.h"
#include <sqlite_orm/sqlite_orm.h>
#include <exception>

namespace crs::core::user
{
    user user_repository::get_by_id(int id)
    {
        using namespace crs::core;

        auto db = core::storage::storage::get_instance()->get_db();
        auto user_data = db.get_pointer<core::storage::user_data>(id);
        if (user_data)
        {
            return user(user_data->name, user_data->password_hash);
        }
        else
        {
            throw core::core_exception("no user with id ");
        }
    }

    void user_repository::save(user* user_to_add)
    {
        using namespace crs::core;

        auto db = storage::storage::get_instance()->get_db();
        auto user_data = storage::user_data{
            .name = user_to_add->get_name(),
            .password_hash = user_to_add->get_password_hash(),
            //            .role =user_to_add->get_role()
        };

        db.insert(user_data);
    }

    user* user_repository::get_by_username(std::string username)
    {
        using namespace crs::core::storage;

        auto db = crs::core::storage::storage::get_instance()->get_db();

        try
        {
            using namespace sqlite_orm;

            auto user_raw = db.get_all<user_data>(
                where(is_equal(&user_data::name, username))
            );
            if (user_raw.size() != 1)
            {
                throw core::core_exception("User not found!");
            }
            return new user(user_raw.front().name, user_raw.front().password_hash);
        }
        catch (std::exception& exception)
        {
            throw core::core_exception("User not found!");
        }
    }

}


