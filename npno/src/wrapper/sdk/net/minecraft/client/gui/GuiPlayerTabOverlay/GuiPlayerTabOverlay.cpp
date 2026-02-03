#include "GuiPlayerTabOverlay.h"

GuiPlayerTabOverlay::GuiPlayerTabOverlay(const jobject instance)
    : JavaClass(instance)
{

}

GuiPlayerTabOverlay::~GuiPlayerTabOverlay() = default;

auto GuiPlayerTabOverlay::GetPlayerName(const std::unique_ptr<NetworkPlayerInfo>& playerInfo) const -> std::string
{
    jni::frame f;

    return JavaUtil::JStringToString(static_cast<jstring>(jobject(maps::GuiPlayerTabOverlay(this->instance).getPlayerName.call((playerInfo->GetInstance())))));
}