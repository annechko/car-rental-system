#include "storage.h"
#include <core/user/user.h>

crs::core::storage::storage* crs::core::storage::storage::instance_ = nullptr;

crs::core::storage::storage* crs::core::storage::storage::get_instance()
{
    if (instance_ == nullptr)
    {
        instance_ = new crs::core::storage::storage();
    }
    return instance_;
}
crs::core::storage::storage::storage()
{
    db_.sync_schema();
}

