#include "storage.h"
#include <memory>

namespace crs::core::storage
{
    storage* storage::instance_ = nullptr;

    storage* storage::get_instance()
    {
        if (instance_ == nullptr)
        {
            instance_ = new storage();
        }
        return instance_;
    }

    storage::storage()
    {
        static auto db = init_storage(getenv("ENV_TEST") == NULL ? "storage.sqlite" : "storage_test.sqlite");

        db_ = &db;
        db_->sync_schema();
    }

    db* storage::get_db()
    {
        return db_;
    }
}
