#ifndef _USER_H_
#define _USER_H_

#include <string>

namespace crs::core::user
{
    enum USER_ROLE
    {
        CUSTOMER = 0, ADMIN = 1
    };

    const int MAX_NAME_LENGTH = 30;

    class user
    {

        public:
            user(std::string name, std::string password_hash);
            const std::string get_name() const;
            const std::string get_password_hash() const;
            const crs::core::user::USER_ROLE get_role() const;
        private:
            std::string name_;
            std::string password_hash_;
            void validate_name(std::string username);

    };

}

#endif //_USER_H_
