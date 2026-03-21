#pragma once

#include "../entity_living_base.hpp"

#include "inventory_player.hpp"

namespace jni
{
	class entity_player : public jni::entity_living_base
	{
	public:
		explicit entity_player(const jobject instance)
			: jni::entity_living_base{ instance }
		{

		}

		auto get_name() const
			-> std::string
		{
			return get_method<std::string>(mapping::entity_player::getName)->call();
		}

		auto get_inventory() const
			-> std::unique_ptr<jni::inventory_player>
		{
			return get_field<jni::inventory_player>(mapping::entity_player::inventory)->get();
		}
	};
}