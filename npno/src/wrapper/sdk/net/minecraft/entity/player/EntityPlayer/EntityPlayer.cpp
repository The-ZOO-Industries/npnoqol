#include "EntityPlayer.h"

EntityPlayer::EntityPlayer(maps::EntityPlayer instance)
    : EntityLivingBase(maps::EntityLivingBase(instance.object_instance, instance.is_global()))
{

}

EntityPlayer::~EntityPlayer() = default;

bool EntityPlayer::IsSpectator() const
{
    return static_cast<bool>(maps::EntityPlayer(this->instance.object_instance).isSpectator.call());
}

bool EntityPlayer::IsUsingItem() const
{
    return static_cast<bool>(maps::EntityPlayer(this->instance.object_instance).isBlocking.call());
}

bool EntityPlayer::CanAttackPlayer(const std::unique_ptr<EntityPlayer>& target) const
{
    maps::EntityPlayer targetParam{ target->GetInstance().object_instance };
    return static_cast<bool>(maps::EntityPlayer(this->instance.object_instance).canAttackPlayer.call(targetParam));
}

std::string EntityPlayer::GetCustomNameTag() const
{
    maps::String nameTag = maps::EntityPlayer(this->instance.object_instance).getCustomNameTag.call();
    return JavaUtil::JStringToString((jstring)jobject(nameTag));
}

std::unique_ptr<GameProfile> EntityPlayer::GetGameProfile() const
{
    maps::GameProfile gameProfile = maps::EntityPlayer(this->instance.object_instance).getGameProfile.call();
    maps::GameProfile globalProfile{ gameProfile.object_instance, true };
    return std::make_unique<GameProfile>(globalProfile);
}