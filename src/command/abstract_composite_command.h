#ifndef ABSTRACT_COMPOSITE_COMMAND_H
#define ABSTRACT_COMPOSITE_COMMAND_H
#include "abstract_command.h"
#include "input_parser.h"

namespace crs
{
    namespace command
    {
        class abstract_composite_command : abstract_command
        {
        public:
            abstract_composite_command();
            virtual ~abstract_composite_command()
            {
            }

        };
    }
}



#endif //ABSTRACT_COMPOSITE_COMMAND_H
