#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <string>
namespace crs
{
    namespace command
    {
        class input_parser
        {
        public:
            input_parser(char** begin, char** end) : begin_(begin), end_(end)
            {
            };
            bool has(std::string name);
        private:
            char** begin_;
            char** end_;
            bool cmd_option_exists(char** begin, char** end, const std::string& option);
        };
    }
}

#endif //INPUT_PARSER_H
