#pragma once

#include "entity.hpp"

#include "../potion/potion_effect.hpp"

namespace jni
{
	class entity_living_base : public jni::entity
	{
	public:
		explicit entity_living_base(const jobject instance)
			: jni::entity{ instance }
		{

		}

		auto get_health() const
			-> float
		{
			return get_method<float>(mapping::entity_living_base::getHealth)->call();
		}

		auto get_max_health() const
			-> float
		{
			return get_method<float>(mapping::entity_living_base::getMaxHealth)->call();
		}

		auto get_absorption_amount() const
			-> float
		{
			return get_method<float>(mapping::entity_living_base::getAbsorptionAmount)->call();
		}

		auto get_active_potion_effects() const
			-> std::vector<std::unique_ptr<jni::potion_effect>>
		{
			return get_method<jni::collection>(mapping::entity_living_base::getActivePotionEffects)->call()->to_vector<jni::potion_effect>();
		}
	};
}