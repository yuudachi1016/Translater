#pragma once
#include <string>
class File
{
public:
    // ��ȡ�ļ�
    static std::string ReadFile(const std::string& filename);

    // д���ļ�
    static void WriteFile(const std::string& filename, const std::string& fileBin);
};
