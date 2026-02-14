#include "GuiIngame.h"

GuiIngame::GuiIngame(maps::GuiIngame instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

GuiIngame::~GuiIngame() = default;

std::unique_ptr<GuiNewChat> GuiIngame::GetPersistantChatGUI() const
{
    maps::GuiNewChat chatGUI = maps::GuiIngame(this->instance.object_instance).persistantChatGUI.get();
    maps::GuiNewChat globalChatGUI{ chatGUI.object_instance, true };
    return std::make_unique<GuiNewChat>(globalChatGUI);
}

std::unique_ptr<GuiPlayerTabOverlay> GuiIngame::GetOverlayPlayerList() const
{
    maps::GuiPlayerTabOverlay playerList = maps::GuiIngame(this->instance.object_instance).overlayPlayerList.get();
    maps::GuiPlayerTabOverlay globalPlayerList{ playerList.object_instance, true };
    return std::make_unique<GuiPlayerTabOverlay>(globalPlayerList);
}