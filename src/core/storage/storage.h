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
        std::string password_hash;
        //        crs::core::user::USER_ROLE role;
    };

    inline auto init_storage(const std::string& path)
    {
        using namespace sqlite_orm;
        return make_storage(path,
            make_table("user",
                make_column("id", &user_data::id, primary_key()),
                make_column("name", &user_data::name, unique()),
                make_column("password_hash", &user_data::password_hash)
            ));
    }

    using Db = decltype(init_storage("storage.sqlite"));

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
            Db db_ = init_storage("storage.sqlite");
    };
}


#endif //STORAGE_H
