#include "PotionEffect.h"

PotionEffect::PotionEffect(maps::PotionEffect instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

PotionEffect::~PotionEffect() = default;

I32 PotionEffect::GetDuration() const
{
    return static_cast<I32>(maps::PotionEffect(this->instance.object_instance).getDuration.call());
}

I32 PotionEffect::GetAmplifier() const
{
    return static_cast<I32>(maps::PotionEffect(this->instance.object_instance).getAmplifier.call());
}

std::string PotionEffect::GetEffectName() const
{
    maps::String effectName = maps::PotionEffect(this->instance.object_instance).getEffectName.call();
    return JavaUtil::JStringToString((jstring)jobject(effectName));
}