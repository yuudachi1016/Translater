#include <iostream>
#include "BaiDuEngine.h"
#include "URLEncode.h"
#include <thread>
#include <chrono>
using namespace std;
int main()
{
    // �������ı�
    std::string str  = u8"ƻ��";
    std::string str2 = u8"ѩ��";

    std::vector<std::string> vec;
    vec.push_back(str);
    vec.push_back(str2);

    // ����
    std::string encode = URLEncode::encode(str);
    cout << encode << endl;

    // ������
    std::string result;

    EngineBase* ptr = new BaiDuEngine();
    ptr->SetFromLanguage("zh");
    ptr->SetToLanguage("en");

    result = ptr->TranslateText(str);
    cout << result << endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::vector<std::string> result2;
    result2 = ptr->TranslateBatch(vec);
    for (auto& dst : result2)
    {
        cout << "dst��" << dst << endl;
    }
}
