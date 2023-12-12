#ifndef USER_H
#define USER_H
#include "abstract_composite_command.h"

namespace crs::command
{
    class user : public abstract_composite_command
    {
        public:
            user();
            const std::string get_name() const override;
    };
}


#endif


