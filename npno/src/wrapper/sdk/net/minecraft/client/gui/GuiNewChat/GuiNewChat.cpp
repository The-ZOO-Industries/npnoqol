#include "GuiNewChat.h"

GuiNewChat::GuiNewChat(const jobject instance)
    : JavaClass(instance)
{

}

GuiNewChat::~GuiNewChat() = default;

std::vector<std::unique_ptr<ChatLine>> GuiNewChat::GetChatLines() const
{
    jni::frame f;

    std::vector<std::unique_ptr<ChatLine>> chat;

    maps::List listWrapper = maps::GuiNewChat(this->instance).chatLines.get();

    jni::array<maps::Object> array = ((maps::Collection)listWrapper).toArray.call();

    std::vector<maps::Object> vec = array.to_vector();

    for (maps::Object& obj : vec)
    {
        chat.emplace_back(std::make_unique<ChatLine>(jobject(maps::ChatLine(obj, true))));
    }

    return chat;
}

void GuiNewChat::RefreshChat() const
{
    maps::GuiNewChat(this->instance).refreshChat.call();
}

void GuiNewChat::DeleteChatLine(const I32 id) const
{
    maps::GuiNewChat(this->instance).deleteChatLine.call(static_cast<jint>(id));
}