#pragma once

#include "../../world/world.hpp"

namespace jni
{
	class world_client final : public jni::world
	{
	public:
		explicit world_client(const jobject instance)
			: world{ instance }
		{

		}
	};
}