#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>

class StringUtils
{
public:
    static std::string padRight(std::string &str, const int size, const char sign)
    {
        std::string result = str;
        for (int i = 0; i < size - str.length(); i++)
            result += sign;

        return result;
    }
};

#endif