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