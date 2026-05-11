#pragma once

#include "../../mapping.hpp"

namespace sdk
{
	class uuid : public vmhook::object<sdk::uuid>
	{
	public:
		explicit uuid(const vmhook::oop_type_t instance) noexcept
			: vmhook::object<sdk::uuid>{ instance }
		{

		}

		auto version() const noexcept
			-> int
		{
			return get_method("version")->call();
		}
	};
}