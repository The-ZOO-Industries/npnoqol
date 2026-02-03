#include "ChatLine.h"

ChatLine::ChatLine(const jobject instance)
    : JavaClass(instance)
{

}

ChatLine::~ChatLine() = default;

I32 ChatLine::GetChatLineID() const
{
    return static_cast<I32>(maps::ChatLine(this->instance).chatLineID.get());
}

std::unique_ptr<IChatComponent> ChatLine::GetLineString() const
{
    jni::frame f;

    return std::make_unique<IChatComponent>(jni::make_global(maps::ChatLine(this->instance).lineString.get()));
}

void ChatLine::SetLineString(const std::unique_ptr<IChatComponent>& newLine)
{
    jni::frame f;
    
    maps::ChatLine(this->instance).lineString.set(newLine->GetInstance());
}