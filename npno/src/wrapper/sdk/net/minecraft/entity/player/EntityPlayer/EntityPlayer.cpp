#include "EntityPlayer.h"

EntityPlayer::EntityPlayer(const jobject instance)
	: EntityLivingBase(instance)
{

}

EntityPlayer::~EntityPlayer() = default;

bool EntityPlayer::IsSpectator() const
{
	return static_cast<bool>(maps::EntityPlayer(this->instance).isSpectator.call());
}

bool EntityPlayer::IsUsingItem() const
{
	return static_cast<bool>(maps::EntityPlayer(this->instance).isBlocking.call());
}

bool EntityPlayer::CanAttackPlayer(const std::unique_ptr<EntityPlayer>& target) const
{
	jni::frame f;

	maps::EntityPlayer targetParam(target->GetInstance());
	return static_cast<bool>(maps::EntityPlayer(this->instance).canAttackPlayer.call(targetParam));
}

std::string EntityPlayer::GetCustomNameTag() const
{
	jni::frame f;

	return JavaUtil::JStringToString(static_cast<jstring>(maps::EntityPlayer(this->instance).getCustomNameTag.call()));
}

std::unique_ptr<GameProfile> EntityPlayer::GetGameProfile() const
{
	jni::frame f;

	return std::make_unique<GameProfile>(jni::make_global(maps::EntityPlayer(this->instance).getGameProfile.call()));
}