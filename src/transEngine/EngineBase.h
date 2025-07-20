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

    // �����ı�
    virtual std::string TranslateText(const std::string& text) = 0;

    // ��������
    virtual std::vector<std::string> TranslateBatch(const std::vector<std::string>& texts) = 0;

protected:
    // ��ȡ�����ļ�
    virtual void LoadDataFile() = 0;

    // �ı�����
    virtual std::vector<std::string> GetTextGroup(const std::vector<std::string>& text) = 0;

    // ��������
    virtual std::string GetRequst(const std::string&)              = 0;
    virtual std::string GetRequst(const std::vector<std::string>&) = 0;

    // ��������
    virtual std::vector<std::tuple<std::string, std::string>> ToRequst(const std::string&) = 0;

    // ������
    virtual std::vector<std::tuple<std::string, std::string>> GetResult(const std::string&) = 0;

    std::string GetRequstURL() const;

protected:
    std::string m_from;      // Դ����
    std::string m_to;        // Ŀ������
    std::string m_requstURL; // ��������
    std::string m_apiKey;    // key
    int m_qpsMax;            // ÿ�����������
    int m_lengthMax;         // ����������󳤶�
};
