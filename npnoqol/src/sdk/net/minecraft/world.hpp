#pragma once

#include "../../mapping.hpp"

namespace sdk
{
	class world : public vmhook::object<sdk::world>
	{
	public:
		explicit world(const vmhook::oop_type_t instance) noexcept
			: vmhook::object<sdk::world>{ instance }
		{

		}
	};
}
