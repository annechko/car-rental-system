#ifndef _USER_H_
#define _USER_H_

#include <string>

namespace crs
{
    namespace core
    {
        namespace user
        {
            struct ROLE {
                enum USER_ROLE
                {
                    CUSTOMER = 0, ADMIN = 1
                };
            };

            class user
            {

            public:
                user(std::string n) : name_(n) {}
                std::string get_name() const {return name_;};
                crs::core::user::ROLE::USER_ROLE get_role() const;
            private:
                std::string name_;
            };

        }
    }
}

#endif //_USER_H_
