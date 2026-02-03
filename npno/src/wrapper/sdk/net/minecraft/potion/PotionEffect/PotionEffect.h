#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

class PotionEffect final : public JavaClass
{
public:
	explicit PotionEffect(const jobject instance);

	virtual ~PotionEffect() override;

	[[nodiscard]] I32 GetDuration() const;
	[[nodiscard]] I32 GetAmplifier() const;

	[[nodiscard]] std::string GetEffectName() const;
};

namespace maps
{
    BEGIN_KLASS_DEF(PotionEffect, "net/minecraft/potion/PotionEffect")
        jni::method<jint, "getDuration"> getDuration{ *this };
        jni::method<jint, "getAmplifier"> getAmplifier{ *this };
        jni::method<String, "getEffectName"> getEffectName{ *this };
    END_KLASS_DEF()
}