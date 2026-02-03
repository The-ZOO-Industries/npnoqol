#pragma once

#include "../../src/wrapper/sdk/net/minecraft/entity/EntityLivingBase/EntityLivingBase.h"

#include "../../src/wrapper/sdk/com/mojang/authlib/GameProfile/GameProfile.h"

class EntityPlayer : public EntityLivingBase
{
public:
	explicit EntityPlayer(const jobject instance);

	virtual ~EntityPlayer() override;

	[[nodiscard]] virtual bool IsSpectator() const final;
	[[nodiscard]] virtual bool IsUsingItem() const final;

	[[nodiscard]] virtual bool CanAttackPlayer(const std::unique_ptr<EntityPlayer>& target) const final;

	[[nodiscard]] virtual std::string GetCustomNameTag() const final;

	[[nodiscard]] std::unique_ptr<GameProfile> GetGameProfile() const;
};

namespace maps
{
    BEGIN_KLASS_DEF_EX(EntityPlayer, "net/minecraft/entity/player/EntityPlayer", EntityLivingBase)
        jni::method<jboolean, "isSpectator"> isSpectator{ *this };
        jni::method<jboolean, "isBlocking"> isBlocking{ *this };
        jni::method<jboolean, "canAttackPlayer", jni::NOT_STATIC, EntityPlayer> canAttackPlayer{ *this };
        jni::method<String, "getCustomNameTag"> getCustomNameTag{ *this };
        jni::method<GameProfile, "getGameProfile"> getGameProfile{ *this };
    END_KLASS_DEF()
}