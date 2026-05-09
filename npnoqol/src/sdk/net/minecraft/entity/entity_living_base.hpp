#pragma once

#include "entity.hpp"

namespace sdk
{
	class entity_living_base : public sdk::entity
	{
	public:
		explicit entity_living_base(const vmhook::oop_type_t instance) noexcept
			: sdk::entity{ instance }
		{

		}
	};
}
