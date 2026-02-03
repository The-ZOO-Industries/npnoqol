#include "PotionEffect.h"

PotionEffect::PotionEffect(const jobject instance)
    : JavaClass(instance)
{

}

PotionEffect::~PotionEffect() = default;

I32 PotionEffect::GetDuration() const
{
    return static_cast<I32>(maps::PotionEffect(this->instance).getDuration.call());
}

I32 PotionEffect::GetAmplifier() const
{
    return static_cast<I32>(maps::PotionEffect(this->instance).getAmplifier.call());
}

std::string PotionEffect::GetEffectName() const
{
    jni::frame f;

    return JavaUtil::JStringToString(static_cast<jstring>(maps::PotionEffect(this->instance).getEffectName.call()));
}