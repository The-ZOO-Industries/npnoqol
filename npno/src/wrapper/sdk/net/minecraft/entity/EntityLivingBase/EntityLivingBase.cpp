#include "EntityLivingBase.h"

EntityLivingBase::EntityLivingBase(const jobject instance)
	: Entity(instance)
{
	
}

EntityLivingBase::~EntityLivingBase() = default;

float EntityLivingBase::GetHealth() const
{
	return static_cast<float>(maps::EntityLivingBase(this->instance).getHealth.call());
}

float EntityLivingBase::GetMaxHealth() const
{
	return static_cast<float>(maps::EntityLivingBase(this->instance).getMaxHealth.call());
}

float EntityLivingBase::GetAbsorptionAmount() const
{
	return static_cast<float>(maps::EntityLivingBase(this->instance).getAbsorptionAmount.call());
}

std::vector<std::unique_ptr<PotionEffect>> EntityLivingBase::GetActivePotionEffects() const
{
	jni::frame f;

	std::vector<std::unique_ptr<PotionEffect>> potionList;

	maps::Collection collection = maps::EntityLivingBase(this->instance).getActivePotionEffects.call();
	std::vector<maps::Object> vec = collection.toArray().to_vector();

	for (maps::Object& obj : vec)
	{
		potionList.push_back(std::make_unique<PotionEffect>(jni::make_global(obj)));
	}

	return potionList;
}