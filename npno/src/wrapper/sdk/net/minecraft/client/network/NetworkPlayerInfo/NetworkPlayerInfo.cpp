#include "NetworkPlayerInfo.h"

NetworkPlayerInfo::NetworkPlayerInfo(maps::NetworkPlayerInfo instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

NetworkPlayerInfo::~NetworkPlayerInfo() = default;

std::unique_ptr<GameProfile> NetworkPlayerInfo::GetGameProfile() const
{
    maps::GameProfile gameProfile = maps::NetworkPlayerInfo(this->instance.object_instance).getGameProfile.call();
    maps::GameProfile globalProfile{ gameProfile.object_instance, true };
    return std::make_unique<GameProfile>(globalProfile);
}

std::unique_ptr<IChatComponent> NetworkPlayerInfo::GetDisplayName() const
{
    maps::IChatComponent displayName = maps::NetworkPlayerInfo(this->instance.object_instance).getDisplayName.call();
    maps::IChatComponent globalName{ displayName.object_instance, true };
    return std::make_unique<IChatComponent>(globalName);
}

void NetworkPlayerInfo::SetDisplayName(const std::unique_ptr<IChatComponent>& newName)
{
    maps::IChatComponent nameParam{ newName->GetInstance().object_instance };
    maps::NetworkPlayerInfo(this->instance.object_instance).setDisplayName.call(nameParam);
}