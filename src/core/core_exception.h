#ifndef CORE_EXCEPTION_H
#define CORE_EXCEPTION_H

#include <exception>
using namespace std;
namespace crs
{
    namespace core
    {
        class core_exception : public std::exception
        {
        public:
            core_exception(const std::string& msg) throw(): message(msg)
            {
            }
            virtual ~core_exception() throw()
            {
            }

            const char* what() const throw()
            {
                return message.c_str();
            }

        private:
            std::string message;
        };
    }
}

#endif //CORE_EXCEPTION_H
