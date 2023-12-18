#ifndef _USER_H_
#define _USER_H_

#include <string>

namespace crs::core::user
{
    enum USER_ROLE
    {
        CUSTOMER = 0,
        ADMIN = 1
    };

    const int MAX_NAME_LENGTH = 30;

    class user
    {
        public:
            user();
            user(std::string name, std::string password_hash);
            void make_admin();
            const std::string get_name() const;
            void set_name(const std::string& name);
            const std::string get_password_hash() const;
            void set_password_hash(const std::string& password_hash);
            const USER_ROLE get_role() const;
            const int get_role_value() const;
            void set_role_value(int role);
            const int get_id() const;
            void set_id(int id);
            bool is_admin() const;
            bool is_customer() const;
        private:
            int id_;
            std::string name_;
            std::string password_hash_;
            USER_ROLE role_;
            void validate_name(std::string username);

    };

}

#endif
