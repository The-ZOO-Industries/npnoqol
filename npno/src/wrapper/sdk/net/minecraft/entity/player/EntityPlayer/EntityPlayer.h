#pragma once

#include "../../src/wrapper/sdk/net/minecraft/entity/EntityLivingBase/EntityLivingBase.h"
#include "../../src/wrapper/sdk/com/mojang/authlib/GameProfile/GameProfile.h"

class EntityPlayer : public EntityLivingBase
{
public:
    explicit EntityPlayer(maps::EntityPlayer instance);

    virtual ~EntityPlayer() override;

    [[nodiscard]] virtual bool IsSpectator() const final;
    [[nodiscard]] virtual bool IsUsingItem() const final;

    [[nodiscard]] virtual bool CanAttackPlayer(const std::unique_ptr<EntityPlayer>& target) const final;

    [[nodiscard]] virtual std::string GetCustomNameTag() const final;

    [[nodiscard]] std::unique_ptr<GameProfile> GetGameProfile() const;
};