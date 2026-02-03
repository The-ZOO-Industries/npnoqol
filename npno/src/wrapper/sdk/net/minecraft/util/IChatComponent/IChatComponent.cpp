#include "IChatComponent.h"

IChatComponent::IChatComponent(const jobject instance)
    : JavaClass(instance)
{

}

IChatComponent::~IChatComponent() = default;

std::string IChatComponent::GetFormattedText() const
{
    jni::frame f;

    return JavaUtil::JStringToString(static_cast<jstring>(maps::IChatComponent(this->instance).getFormattedText.call()));
}

std::string IChatComponent::GetUnformattedText() const
{
    jni::frame f;
    
    return JavaUtil::JStringToString(static_cast<jstring>(maps::IChatComponent(this->instance).getUnformattedText.call()));
}