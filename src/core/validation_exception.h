#ifndef VALIDATION_EXCEPTION_H
#define VALIDATION_EXCEPTION_H

#include <exception>
using namespace std;
namespace crs
{
    namespace core
    {
        class validation_exception : public std::exception
        {
        public:
            validation_exception(const std::string& msg) throw(): message(msg)
            {
            }
            virtual ~validation_exception() throw()
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

#endif //VALIDATION_EXCEPTION_H
