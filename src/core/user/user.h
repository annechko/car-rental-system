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
                user();
                std::string get_name() const;
                crs::core::user::ROLE::USER_ROLE get_role() const;
            };

        }
    }
}

#endif //_USER_H_
