#pragma once

#include "../../../../mapping.hpp"

namespace sdk
{
	class entity_player : public vmhook::object<sdk::entity_player>
	{
	public:
		explicit entity_player(const vmhook::oop_type_t instance) noexcept
			: vmhook::object<sdk::entity_player>{ instance }
		{

		}

		auto get_name() const noexcept
			-> std::string
		{
			return get_method(mapping::entity_player::getName)->call();
		}
	};
}
