#pragma once

#include "../../world.hpp"

namespace sdk
{
	class world_client : public sdk::world
	{
	public:
		explicit world_client(const vmhook::oop_type_t instance) noexcept
			: sdk::world{ instance }
		{

		}
	};
}
