#pragma once

#include "../../../mapping.hpp"
#include "../../../java/util/uuid.hpp"

namespace sdk
{
	class entity : public vmhook::object<sdk::entity>
	{
	public:
		explicit entity(const vmhook::oop_type_t instance) noexcept
			: vmhook::object<sdk::entity>{ instance }
		{

		}

		auto get_unique_id() const noexcept
			-> std::unique_ptr<sdk::uuid>
		{
			return get_method(mapping::entity::getUniqueID)->call();
		}
	};
}