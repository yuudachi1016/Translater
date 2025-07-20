#pragma once
#include "EngineBase.h"
class BaiDuEngine : public EngineBase
{
public:
    BaiDuEngine();
    BaiDuEngine(const BaiDuEngine& reader)            = delete;
    BaiDuEngine& operator=(const BaiDuEngine& reader) = delete;

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
    // ����MD5
    std::string EncryptString(const std::string& str);

private:
    std::string m_appId;
};
