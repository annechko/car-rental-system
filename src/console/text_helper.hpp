#ifndef TEXT_HELPER_HPP
#define TEXT_HELPER_HPP
#include <string>

namespace crs::console
{
    class text_helper
    {
        public:
            static const std::string yellow(const std::string& s)
            {
                return paint(s, "33");
            }

            static const std::string green(const std::string& s)
            {
                return paint(s, "32");
            }

            static const std::string red(const std::string& s)
            {
                return paint(s, "31");
            }

        private:
            static std::string paint(const std::string& s, std::string c)
            {
                return "\x1B[1;" + std::string(c) + "m" + s + "\033[0m";;
            }
    };
}

#endif
