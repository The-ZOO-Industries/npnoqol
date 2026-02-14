#include "GuiNewChat.h"

GuiNewChat::GuiNewChat(maps::GuiNewChat instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

GuiNewChat::~GuiNewChat() = default;

std::vector<std::unique_ptr<ChatLine>> GuiNewChat::GetChatLines() const
{
    std::vector<std::unique_ptr<ChatLine>> chat;

    maps::List listWrapper = maps::GuiNewChat(this->instance.object_instance).chatLines.get();
    maps::Collection collection{ listWrapper.object_instance, listWrapper.is_global() };
    jni::array<maps::Object> array = collection.toArray.call();
    std::vector<maps::Object> vec = array.to_vector();

    for (maps::Object& obj : vec)
    {
        maps::ChatLine chatLine{ obj.object_instance, true };
        chat.emplace_back(std::make_unique<ChatLine>(chatLine));
    }

    return chat;
}

void GuiNewChat::RefreshChat() const
{
    maps::GuiNewChat(this->instance.object_instance).refreshChat.call();
}

void GuiNewChat::DeleteChatLine(const I32 id) const
{
    maps::GuiNewChat(this->instance.object_instance).deleteChatLine.call(static_cast<jint>(id));
}