#ifndef _USER_H_
#define _USER_H_

#include <string>

namespace crs::core::user
{
    struct ROLE
    {
        enum USER_ROLE
        {
            CUSTOMER = 0, ADMIN = 1
        };
    };

    const int MAX_NAME_LENGTH = 30;

    class user
    {

        public:
            user(std::string n);
            std::string get_name() const
            {
                return name_;
            };
            crs::core::user::ROLE::USER_ROLE get_role() const;
        private:
            std::string name_;
            void validate_name(std::string username);

    };

}

#endif //_USER_H_
