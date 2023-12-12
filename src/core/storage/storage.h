#ifndef STORAGE_H
#define STORAGE_H
#include <sqlite_orm/sqlite_orm.h>
#include <core/user/user.h>

namespace crs::core::storage
{
    struct user_data
    {
        int id;
        std::string name;
        crs::core::user::ROLE::USER_ROLE role;
    };
    inline auto initStorage(const std::string& path)
    {
        using namespace sqlite_orm;
        return make_storage(path,
            make_table("user",
                make_column("id", &user_data::id, primary_key()),
                make_column("name", &user_data::name)));
    }
    using Db = decltype(initStorage("storage.sqlite"));

    class storage
    {
        public:
            storage(storage& other) = delete;
            void operator=(const storage&) = delete;
            static storage* get_instance();
            Db get_db()
            {
                return db_;
            };
        private:
            static storage* instance_;
            storage();
            Db db_ = initStorage("storage.sqlite");
    };
}


#endif //STORAGE_H
