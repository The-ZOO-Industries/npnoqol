#include "GuiNewChat.h"

GuiNewChat::GuiNewChat(const jobject instance)
    : JavaClass(instance)
{
}

GuiNewChat::~GuiNewChat() = default;

auto GuiNewChat::GetChatLines() const -> std::vector<std::unique_ptr<ChatLine>>
{
    jni::frame f;

    std::vector<std::unique_ptr<ChatLine>> chat{};

    maps::List lines = maps::GuiNewChat(this->instance).chatLines.get();
    std::vector<maps::Object> vec = lines.toArray().to_vector();

    for (maps::Object& obj : vec)
    {
        chat.push_back(
            std::make_unique<ChatLine>(
                jobject(maps::ChatLine(obj, true))
            )
        );
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