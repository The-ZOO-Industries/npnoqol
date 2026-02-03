#include "GuiPlayerTabOverlay.h"

GuiPlayerTabOverlay::GuiPlayerTabOverlay(const jobject instance)
    : JavaClass(instance)
{

}

GuiPlayerTabOverlay::~GuiPlayerTabOverlay() = default;

std::string GuiPlayerTabOverlay::GetPlayerName(const std::unique_ptr<NetworkPlayerInfo>& playerInfo) const 
{
    jni::frame f;

    return JavaUtil::JStringToString(static_cast<jstring>(maps::GuiPlayerTabOverlay(this->instance).getPlayerName.call(infoParam(playerInfo->GetInstance()));
}