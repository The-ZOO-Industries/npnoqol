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

	maps::List lines = maps::GuiNewChat(this->instance).chatLines.get();
	std::vector<maps::Object> vec = lines.toArray().to_vector();

	for (maps::Object& obj : vec)
	{
		chat.push_back(std::make_unique<ChatLine>(jni::make_global(obj)));
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