#pragma once

#include "../entity_living_base.hpp"

namespace jni
{
	class entity_armor_stand final: public jni::entity_living_base
	{
	public:
		explicit entity_armor_stand(const jobject instance)
			: jni::entity_living_base{ instance }
		{

		}

		
	};
}