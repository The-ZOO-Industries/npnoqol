#pragma once

#include "../../src/wrapper/sdk/net/minecraft/entity/Entity/Entity.h"

#include "../../src/wrapper/sdk/net/minecraft/potion/PotionEffect/PotionEffect.h"

class EntityLivingBase : public Entity
{
public:
	explicit EntityLivingBase(const jobject instance);

	virtual ~EntityLivingBase() override;

	[[nodiscard]] virtual float GetHealth() const final;
	[[nodiscard]] virtual float GetMaxHealth() const final;
	[[nodiscard]] virtual float GetAbsorptionAmount() const final;

	[[nodiscard]] virtual std::vector<std::unique_ptr<PotionEffect>> GetActivePotionEffects() const final;
};

namespace maps
{
    BEGIN_KLASS_DEF_EX(EntityLivingBase, "net/minecraft/entity/EntityLivingBase", Entity)
        jni::method<jfloat, "getHealth"> getHealth{ *this };
        jni::method<jfloat, "getMaxHealth"> getMaxHealth{ *this };
        jni::method<jfloat, "getAbsorptionAmount"> getAbsorptionAmount{ *this };
        jni::method<Collection, "getActivePotionEffects"> getActivePotionEffects{ *this };
    END_KLASS_DEF()
}