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
	};
}