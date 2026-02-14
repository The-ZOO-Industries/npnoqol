#include "EntityLivingBase.h"

EntityLivingBase::EntityLivingBase(maps::EntityLivingBase instance)
    : Entity(maps::Entity(instance.object_instance, instance.is_global()))
{

}

EntityLivingBase::~EntityLivingBase() = default;

float EntityLivingBase::GetHealth() const
{
    return static_cast<float>(maps::EntityLivingBase(this->instance.object_instance).getHealth.call());
}

float EntityLivingBase::GetMaxHealth() const
{
    return static_cast<float>(maps::EntityLivingBase(this->instance.object_instance).getMaxHealth.call());
}

float EntityLivingBase::GetAbsorptionAmount() const
{
    return static_cast<float>(maps::EntityLivingBase(this->instance.object_instance).getAbsorptionAmount.call());
}

std::vector<std::unique_ptr<PotionEffect>> EntityLivingBase::GetActivePotionEffects() const
{
    std::vector<std::unique_ptr<PotionEffect>> potionList{};

    maps::Collection collection = maps::EntityLivingBase(this->instance.object_instance).getActivePotionEffects.call();
    jni::array<maps::Object> array = collection.toArray.call();
    std::vector<maps::Object> vec = array.to_vector();

    for (maps::Object& obj : vec)
    {
        maps::PotionEffect potion{ obj.object_instance, true };
        potionList.push_back(std::make_unique<PotionEffect>(potion));
    }

    return potionList;
}