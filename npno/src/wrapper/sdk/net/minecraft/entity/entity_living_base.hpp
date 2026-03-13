#pragma once

#include "entity.hpp"

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
			return get_method<float>("getHealth")->call();
		}

		auto get_max_health() const
			-> float
		{
			return get_method<float>("getMaxHealth")->call();
		}

		auto get_absorption_amount() const
			-> float
		{
			return get_method<float>("getAbsorptionAmount")->call();
		}
	};
}