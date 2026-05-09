#pragma once

#include "../../../mapping.hpp"

namespace sdk
{
	class entity : public vmhook::object<sdk::entity>
	{
	public:
		explicit entity(const vmhook::oop_type_t instance) noexcept
			: vmhook::object<sdk::entity>{ instance }
		{

		}
	};
}
