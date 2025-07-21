#pragma once
#include <string>
#include <tuple>
#include <vector>
class RequstAPI
{
public:
    static std::string Requst_GET(const std::string& url);

    static std::string Requst_POST(const std::string& url, const std::string& body, const std::vector<std::tuple<std::string, std::string>>& headers);
};
