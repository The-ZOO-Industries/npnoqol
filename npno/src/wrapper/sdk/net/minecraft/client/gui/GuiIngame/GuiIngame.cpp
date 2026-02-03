#include "GuiIngame.h"

GuiIngame::GuiIngame(const jobject instance)
	: JavaClass(instance)
{

}

GuiIngame::~GuiIngame() = default;

std::unique_ptr<GuiNewChat> GuiIngame::GetPersistantChatGUI() const
{
	jni::frame f;

	return std::make_unique<GuiNewChat>(jni::make_global(maps::GuiIngame(this->instance).persistantChatGUI.get()));
}

std::unique_ptr<GuiPlayerTabOverlay> GuiIngame::GetOverlayPlayerList() const 
{
	jni::frame f;

	return std::make_unique<GuiPlayerTabOverlay>(jni::make_global(maps::GuiIngame(this->instance).overlayPlayerList.get()));
}