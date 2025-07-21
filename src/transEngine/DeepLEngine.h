#pragma once
#include "EngineBase.h"
class DeepLEngine : public EngineBase
{
public:
    DeepLEngine();
    DeepLEngine(const DeepLEngine& reader)            = delete;
    DeepLEngine& operator=(const DeepLEngine& reader) = delete;

    // �����ı�
    std::string TranslateText(const std::string& text);

    // ��������
    std::vector<std::string> TranslateBatch(const std::vector<std::string>& texts);

protected:
    // ��ȡ�����ļ�
    void LoadDataFile();

    // �ı�����
    std::vector<TextBlock> GetTextGroup(const std::vector<std::string>& text);

    // ��������
    std::string GetRequst(const std::string& str);
    std::string GetRequst(const std::vector<std::string>& text);

    // ��������
    std::vector<std::tuple<std::string, std::string>> ToRequst(const std::string&);

    // ������
    std::vector<std::tuple<std::string, std::string>> GetResult(const std::string& jsonStr);

private:
    // ��ȡ����ͷ
    std::vector<std::tuple<std::string, std::string>> GetPostHeader();

private:
    int m_reqQuota;
};
