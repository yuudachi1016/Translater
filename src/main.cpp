#include <iostream>
#include <chrono>
#include <thread>

#include "BaiDuEngine.h"
#include "DeepLEngine.h"

#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// data set     ���ݼ�
std::string transText1;
std::string transText2;
std::string transText3;
std::string transText4;
std::vector<std::string> transTextVec;

auto resetFunc = [&]() {
    transTextVec.clear();

    transText1 = "The beauty of life lies in the journey, not the destination. ";
    transText2 = "The greatest glory in living lies not in never falling, but in rising every time we fall.";
    transText3 = u8"ƻ��";
    transText4 = u8"С��";
    transTextVec.push_back(u8"�������ȱ�");
    transTextVec.push_back(u8"��Ҭ����");
    transTextVec.push_back(u8"��������˹");
    transTextVec.push_back(u8"�Ҳ�֪����ȥ�η�����������·�ϡ�");
};

auto printFunc = [](const string& src, const string& dst) {
    cout << "src: " << src << "\tdst: " << dst << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
};
auto printVecFunc = [](const std::vector<std::string>& src, const std::vector<std::string>& dst) {
    cout << "src: "
         << "\tdst: " << endl;
    for (int i = 0; i < dst.size(); i++)
    {
        cout << src[i] << "\t" << dst[i] << endl;
    }
};

void testBaiDuFunc()
{
    resetFunc();
    cout << "BaiDu Engine:" << endl;

    std::shared_ptr<EngineBase> ptr(new BaiDuEngine());
    ptr->SetFromLanguage("en");
    ptr->SetToLanguage("zh");
    printFunc(transText1, ptr->TranslateText(transText1));
    printFunc(transText2, ptr->TranslateText(transText2));

    ptr->SetFromLanguage("zh");
    ptr->SetToLanguage("en");
    printFunc(transText3, ptr->TranslateText(transText3));
    printFunc(transText4, ptr->TranslateText(transText4));

    cout << endl;
    printVecFunc(transTextVec, ptr->TranslateBatch(transTextVec));
    cout << endl;
}

void testDeepLFunc()
{
    resetFunc();
    cout << "DeepL Engine:" << endl;

    std::shared_ptr<EngineBase> ptr(new DeepLEngine());
    ptr->SetFromLanguage("en");
    ptr->SetToLanguage("zh");
    printFunc(transText1, ptr->TranslateText(transText1));
    printFunc(transText2, ptr->TranslateText(transText2));

    ptr->SetFromLanguage("zh");
    ptr->SetToLanguage("en");
    printFunc(transText3, ptr->TranslateText(transText3));
    printFunc(transText4, ptr->TranslateText(transText4));

    cout << endl;
    printVecFunc(transTextVec, ptr->TranslateBatch(transTextVec));
    cout << endl;
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    testBaiDuFunc();

    testDeepLFunc();
}
