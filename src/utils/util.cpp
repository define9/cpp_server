#include "util.hpp"

Util::Util()
{

}

std::string Util::Str2UTF8(const std::string &str)
{
    return QString(str.c_str()).toUtf8().toStdString();
}
