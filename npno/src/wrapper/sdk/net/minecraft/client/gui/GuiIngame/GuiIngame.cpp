#include "GuiIngame.h"

GuiIngame::GuiIngame(const jobject instance)
	: JavaClass(instance)
{

}

GuiIngame::~GuiIngame() = default;

std::unique_ptr<GuiNewChat> GuiIngame::GetPersistantChatGUI() const
{
	jni::frame f;

	return std::make_unique<GuiNewChat>(jobject(maps::GuiNewChat(maps::GuiIngame(this->instance).persistantChatGUI.get(), true)));
}

std::unique_ptr<GuiPlayerTabOverlay> GuiIngame::GetOverlayPlayerList() const
{
	jni::frame f;

	return std::make_unique<GuiPlayerTabOverlay>(jobject(maps::GuiPlayerTabOverlay(maps::GuiIngame(this->instance).overlayPlayerList.get(), true)));
}