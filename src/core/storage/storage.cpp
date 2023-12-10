#include "storage.h"
#include <core/user/user.h>

using namespace crs::core::storage;

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
    db_.sync_schema();
}

