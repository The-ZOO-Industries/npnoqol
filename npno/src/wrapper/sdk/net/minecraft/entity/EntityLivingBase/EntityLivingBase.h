#pragma once

#include "../../src/wrapper/sdk/net/minecraft/entity/Entity/Entity.h"
#include "../../src/wrapper/sdk/net/minecraft/potion/PotionEffect/PotionEffect.h"
#include "../../src/wrapper/sdk/java/util/List/List.h"

class EntityLivingBase : public Entity
{
public:
    explicit EntityLivingBase(maps::EntityLivingBase instance);

    virtual ~EntityLivingBase() override;

    [[nodiscard]] virtual float GetHealth() const final;
    [[nodiscard]] virtual float GetMaxHealth() const final;
    [[nodiscard]] virtual float GetAbsorptionAmount() const final;

    [[nodiscard]] virtual std::vector<std::unique_ptr<PotionEffect>> GetActivePotionEffects() const final;
};