#include "NetworkPlayerInfo.h"

NetworkPlayerInfo::NetworkPlayerInfo(const jobject instance) 
    : JavaClass(instance) 
{

}

NetworkPlayerInfo::~NetworkPlayerInfo() = default;

std::unique_ptr<GameProfile> NetworkPlayerInfo::GetGameProfile() const 
{
    jni::frame f;

    return std::make_unique<GameProfile>(jni::make_global(maps::NetworkPlayerInfo(this->instance).getGameProfile.call()));
}

std::unique_ptr<IChatComponent> NetworkPlayerInfo::GetDisplayName() const 
{
    jni::frame f;

    return std::make_unique<IChatComponent>(jni::make_global(maps::NetworkPlayerInfo(this->instance).getDisplayName.call()));
}

void NetworkPlayerInfo::SetDisplayName(const std::unique_ptr<IChatComponent>& newName)
{
    jni::frame f;
    
    maps::IChatComponent nameParam(newName->GetInstance());
    maps::NetworkPlayerInfo(this->instance).setDisplayName.call(nameParam);
}