#include "user_repository.h"
#include "core/storage/storage.h"
#include "core/core_exception.hpp"
#include <sqlite_orm/sqlite_orm.h>
#include <exception>

namespace crs::core::user
{
    user_repository::user_repository()
    {
        db_ = storage::storage::get_instance()->get_db();
    }

    user* user_repository::get_by_id(int id)
    {
        using namespace crs::core;

        auto user_raw = db_->get_pointer<user>(id);
        if (user_raw)
        {
            return user_raw.release();
        }
        else
        {
            throw core::core_exception("no user with id ");
        }
    }

    void user_repository::save(user* user_to_add)
    {
        using namespace crs::core;

        int id = db_->insert(*user_to_add);
        user_to_add->set_id(id);
    }

    user* user_repository::get_by_username(std::string username)
    {
        using namespace crs::core::storage;

        try
        {
            using namespace sqlite_orm;

            auto user_raw = db_->get_all_pointer<user>(
                where(is_equal(&user::get_name, username))
            );
            if (user_raw.size() != 1)
            {
                throw core::core_exception("User not found!");
            }
            return user_raw.front().release();
        }
        catch (std::exception& exception)
        {
            throw core::core_exception("User not found!");
        }
    }
}


