#include "GuiPlayerTabOverlay.h"

GuiPlayerTabOverlay::GuiPlayerTabOverlay(maps::GuiPlayerTabOverlay instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

GuiPlayerTabOverlay::~GuiPlayerTabOverlay() = default;

std::string GuiPlayerTabOverlay::GetPlayerName(const std::unique_ptr<NetworkPlayerInfo>& playerInfo) const
{
    maps::NetworkPlayerInfo info{ playerInfo->GetInstance().object_instance };
    maps::String playerName = maps::GuiPlayerTabOverlay(this->instance.object_instance).getPlayerName.call(info);
    return JavaUtil::JStringToString((jstring)jobject(playerName));
}