#include "EngineBase.h"

std::string EngineBase::GetRequstURL() const
{
    return m_requstURL;
}

void EngineBase::SetFromLanguage(const std::string& language)
{
    m_from = language;
}

void EngineBase::SetToLanguage(const std::string& language)
{
    m_to = language;
}
