#pragma once

#include "../module.hpp"

namespace zoo
{
	class chat_manager final : public zoo::module
	{
	public:
		chat_manager() noexcept;

		~chat_manager() noexcept;

		auto on_run_tick() noexcept
			-> void override;

		auto on_print_chat_message(vmhook::return_value& return_value, const std::unique_ptr<sdk::i_chat_component>& chat_component) noexcept
			-> bool override;
	};
}
