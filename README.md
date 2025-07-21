# Translater


A simple C++11 translation engine API call implementation.
一个简单的 C++11 翻译引擎API调用实现。



Currently supports Baidu API and Deepl API.
目前支持百度API和Deepl API。

Before use, you need to fill in the corresponding API information in config.txt.
使用前，需要在 config.txt 文件中填写相应的 API 信息。

Basic usage:
基本用法：

```c++

// Create the translation engine needed
// 创建所需的翻译引擎
std::shared_ptr<EngineBase> ptr(new BaiDuEngine());
std::shared_ptr<EngineBase> ptr2(new DeepLEngine());

// Set the language of the text to be translated and the target language type.
// 设置待翻译文本的语言及目标语言类型。
ptr->SetFromLanguage("en");
ptr->SetToLanguage("zh");

// Translate a single text
// 翻译单条文本
ptr->TranslateText(std::string{});

// Translate multiple texts
// 翻译多条文本
ptr->TranslateBatch(std::vector<std::string>{});

```