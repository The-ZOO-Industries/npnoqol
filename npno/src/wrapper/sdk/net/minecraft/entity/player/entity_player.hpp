#pragma once

#include "../entity_living_base.hpp"

namespace jni
{
	class entity_player : public jni::entity_living_base
	{
	public:
		explicit entity_player(const jobject instance)
			: jni::entity_living_base{ instance }
		{

		}
	};
}