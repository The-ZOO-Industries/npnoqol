#include "IChatComponent.h"

IChatComponent::IChatComponent(maps::IChatComponent instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

IChatComponent::~IChatComponent() = default;

std::string IChatComponent::GetFormattedText() const
{
    maps::String formattedText = maps::IChatComponent(this->instance.object_instance).getFormattedText.call();
    return JavaUtil::JStringToString((jstring)jobject(formattedText));
}

std::string IChatComponent::GetUnformattedText() const
{
    maps::String unformattedText = maps::IChatComponent(this->instance.object_instance).getUnformattedText.call();
    return JavaUtil::JStringToString((jstring)jobject(unformattedText));
}