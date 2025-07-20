#include "BaiDuEngine.h"
#include "EncryptMD5.h"
#include "RequstAPI.h"
#include "json.hpp"
#include "URLEncode.h"
#include "File.h"
#include "ThreadPool.h"
#include "RateLimiter.h"

#include <random>
#include <iostream>
#include <tuple>
#include <atomic>
#include <chrono>
#include <thread>
#include <mutex>

BaiDuEngine::BaiDuEngine()
{
    LoadDataFile();
}

std::string BaiDuEngine::TranslateText(const std::string& text)
{
    std::vector<std::tuple<std::string, std::string>> transResults = ToRequst(GetRequst(text));
    if (transResults.empty())
        return std::string();

    std::tuple<std::string, std::string> transResult = transResults[0];
    std::string resutlt                              = std::get<1>(transResult);
    return resutlt;
}

std::vector<std::string> BaiDuEngine::TranslateBatch(const std::vector<std::string>& texts)
{
    std::vector<std::string> result;
    std::mutex resultMutex;
    ThreadPool pool(4);

    // 速率限制器 - 每秒m_qpsMax个请求
    RateLimiter limiter(m_qpsMax);

    std::vector<std::string> reqTexts = GetTextGroup(texts);
    std::vector<std::future<void>> futures;
    for (auto& req : reqTexts)
    {
        auto func = [&]() {
            limiter.wait(); // 等待获取请求许可

            std::vector<std::tuple<std::string, std::string>> res = ToRequst(req);

            std::lock_guard<std::mutex> lock(resultMutex);
            for (auto& srcdst : res)
            {
                result.push_back(std::get<1>(srcdst));
            }
        };
        futures.push_back(pool.enqueue(func));
    }

    for (auto& future : futures)
    {
        future.get();
    }
    return result;
}

void BaiDuEngine::LoadDataFile()
{
    std::string config       = File::ReadFile("config.txt");
    nlohmann::json json_obj  = nlohmann::json::parse(config);
    nlohmann::json baidu_obj = json_obj["engine"]["BaiDu"];

    m_from = json_obj["from"];
    m_to   = json_obj["to"];

    m_requstURL = baidu_obj["requstURL"];
    m_apiKey    = baidu_obj["apiKey"];
    m_appId     = baidu_obj["appId"];

    std::string qps = baidu_obj["qps"];
    if (qps.empty())
        m_qpsMax = 1;
    else
        m_qpsMax = std::atoi(qps.data());

    std::string length = baidu_obj["length"];
    if (length.empty())
        m_lengthMax = 100;
    else
        m_lengthMax = std::atoi(length.data());
}

std::vector<std::string> BaiDuEngine::GetTextGroup(const std::vector<std::string>& fileText)
{
    std::vector<std::string> result;

    int reqLen = 0;
    std::vector<std::string> reqText;
    for (int i = 0; i < fileText.size(); i++)
    {
        if (reqLen + fileText[i].size() >= m_lengthMax)
        {
            if (!reqText.empty())
                result.push_back(GetRequst(reqText));

            reqText.clear();
            reqText.push_back(fileText[i]);
            reqLen = fileText[i].size();
        }
        else
        {
            reqText.push_back(fileText[i]);
            reqLen += fileText[i].size();
        }
    }
    if (!reqText.empty())
    {
        result.push_back(GetRequst(reqText));
    }
    return result;
}

std::string BaiDuEngine::GetRequst(const std::string& str)
{
    std::random_device rd;                          // 用于获取随机数种子
    std::mt19937 gen(rd());                         // 使用随机数种子初始化Mersenne Twister生成器
    std::uniform_int_distribution<> dis(1, 100000); // 定义一个在1到100之间均匀分布的整数生成器
    int random_number = dis(gen);                   // 生成随机数

    std::string salt = std::to_string(random_number); // 随机数
    std::string sign = EncryptString(m_appId + str + salt + m_apiKey);
    std::string url  = m_requstURL;
    url += "?q=" + URLEncode::encode(str);
    url += "&from=" + m_from;
    url += "&to=" + m_to;
    url += "&appid=" + m_appId;
    url += "&salt=" + salt;
    url += "&sign=" + sign;
    return url;
}

std::string BaiDuEngine::GetRequst(const std::vector<std::string>& texts)
{
    std::string requstStr;
    for (auto& text : texts)
    {
        requstStr += text + u8"\n";
    }
    if (requstStr.empty())
        return std::string();
    return GetRequst(requstStr.substr(0, requstStr.size() - 1));
}

std::vector<std::tuple<std::string, std::string>> BaiDuEngine::ToRequst(const std::string& reqStr)
{
    std::string response = RequstAPI::Requst_GET(reqStr);
    return GetResult(response);
}

std::vector<std::tuple<std::string, std::string>> BaiDuEngine::GetResult(const std::string& jsonStr)
{
    if (jsonStr.empty()) return {};

    std::vector<std::tuple<std::string, std::string>> result;

    nlohmann::json json_obj     = nlohmann::json::parse(jsonStr);
    nlohmann::json trans_result = json_obj["trans_result"];
    for (auto& trans : trans_result.items())
    {
        nlohmann::json value = trans.value();
        std::string src      = value["src"];
        std::string dst      = value["dst"];

        result.push_back(std::make_tuple(src, dst));
    }
    return result;
}

std::string BaiDuEngine::EncryptString(const std::string& str)
{
    EncryptMD5 md5;
    return md5.compute(str);
}
