#include "ChatLine.h"

ChatLine::ChatLine(maps::ChatLine instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

ChatLine::~ChatLine() = default;

I32 ChatLine::GetChatLineID() const
{
    return static_cast<I32>(maps::ChatLine(this->instance.object_instance).chatLineID.get());
}

std::unique_ptr<IChatComponent> ChatLine::GetLineString() const
{
    maps::IChatComponent lineString = maps::ChatLine(this->instance.object_instance).lineString.get();
    maps::IChatComponent globalLineString{ lineString.object_instance, true };
    return std::make_unique<IChatComponent>(globalLineString);
}

void ChatLine::SetLineString(const std::unique_ptr<IChatComponent>& newLine)
{
    maps::IChatComponent component{ newLine->GetInstance().object_instance };
    maps::ChatLine(this->instance.object_instance).lineString.set(component);
}