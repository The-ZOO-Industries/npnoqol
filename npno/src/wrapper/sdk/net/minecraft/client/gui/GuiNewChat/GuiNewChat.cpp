#include "GuiNewChat.h"

GuiNewChat::GuiNewChat(const jobject instance)
    : JavaClass(instance)
{
}

GuiNewChat::~GuiNewChat() = default;

auto GuiNewChat::GetChatLines() const -> std::vector<std::unique_ptr<ChatLine>>
{
    jni::frame f;

    std::vector<std::unique_ptr<EntityPlayer>> chat;

    maps::List listWrapper = maps::World(this->instance).playerEntities.get();

    std::vector<maps::Object> vec = ((maps::Collection)listWrapper).toArray.call().to_vector();

    for (maps::Object& obj : vec)
    {
        chat.emplace_back(std::make_unique<EntityPlayer>(jobject(maps::EntityPlayer(obj, true))));
    }

    return chat;
}

auto GuiNewChat::RefreshChat() const -> void
{
    maps::GuiNewChat(this->instance).refreshChat.call();
}

auto GuiNewChat::DeleteChatLine(const I32 id) const -> void
{
    maps::GuiNewChat(this->instance).deleteChatLine.call(jint{ id });
}
