#include "NetworkPlayerInfo.h"

NetworkPlayerInfo::NetworkPlayerInfo(const jobject instance)
    : JavaClass(instance)
{

}

NetworkPlayerInfo::~NetworkPlayerInfo() = default;

auto NetworkPlayerInfo::GetGameProfile() const -> std::unique_ptr<GameProfile>
{
    jni::frame f;

    return std::make_unique<GameProfile>(jobject(maps::GameProfile(maps::NetworkPlayerInfo(this->instance).getGameProfile.call(), true)));
}

auto NetworkPlayerInfo::GetDisplayName() const -> std::unique_ptr<IChatComponent>
{
    jni::frame f;

    return std::make_unique<IChatComponent>(jobject(maps::IChatComponent(maps::NetworkPlayerInfo(this->instance).getDisplayName.call(), true)));
}

auto NetworkPlayerInfo::SetDisplayName(const std::unique_ptr<IChatComponent>& newName) -> void
{
    jni::frame f;

    maps::IChatComponent nameParam{ jobject(maps::IChatComponent(newName->GetInstance(), true)) };
    maps::NetworkPlayerInfo(this->instance).setDisplayName.call(nameParam);
}