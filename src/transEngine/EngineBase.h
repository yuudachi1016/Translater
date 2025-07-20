#pragma once
#include <string>
#include <vector>
class EngineBase
{
public:
    EngineBase(){};
    EngineBase(const EngineBase& reader)            = delete;
    EngineBase& operator=(const EngineBase& reader) = delete;

    void SetFromLanguage(const std::string& language);

    void SetToLanguage(const std::string& language);

    // 翻译文本
    virtual std::string TranslateText(const std::string& text) = 0;

    // 批量翻译
    virtual std::vector<std::string> TranslateBatch(const std::vector<std::string>& texts) = 0;

protected:
    // 读取配置文件
    virtual void LoadDataFile() = 0;

    // 文本分组
    virtual std::vector<std::string> GetTextGroup(const std::vector<std::string>& text) = 0;

    // 生成请求
    virtual std::string GetRequst(const std::string&)              = 0;
    virtual std::string GetRequst(const std::vector<std::string>&) = 0;

    // 发送请求
    virtual std::vector<std::tuple<std::string, std::string>> ToRequst(const std::string&) = 0;

    // 处理结果
    virtual std::vector<std::tuple<std::string, std::string>> GetResult(const std::string&) = 0;

    std::string GetRequstURL() const;

protected:
    std::string m_from;      // 源语言
    std::string m_to;        // 目的语言
    std::string m_requstURL; // 请求链接
    std::string m_apiKey;    // key
    int m_qpsMax;            // 每秒最大请求数
    int m_lengthMax;         // 单次请求最大长度
};
