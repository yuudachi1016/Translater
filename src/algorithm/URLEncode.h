#pragma once
#include <string>
class URLEncode
{
public:
    // URL����
    static std::string encode(const std::string& value);

    // URL����
    static std::string decode(const std::string& value);
};
