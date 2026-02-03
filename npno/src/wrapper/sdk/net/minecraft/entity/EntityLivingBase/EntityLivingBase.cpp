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

	std::vector<std::unique_ptr<PotionEffect>> potionList{};

	maps::Collection collection = maps::NetHandlerPlayClient(this->instance).getPlayerInfoMap.call();
	std::vector<maps::Object> vec = maps::Collection(collection, true).toArray.call().to_vector();

	for (maps::Object& obj : vec)
	{
		potionList.push_back(std::make_unique<PotionEffect>(jobject(maps::PotionEffect(obj, true))));
	}

	return potionList;
}