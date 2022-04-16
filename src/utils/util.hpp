#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <QString>

namespace DataFormat {
    const std::string kJSON = "application/json";
    const std::string kTEXT = "text/html; charset=UTF-8";
}

class Util
{
public:
    Util();

    std::string static Str2UTF8(const std::string &);
};

#endif // UTIL_HPP
