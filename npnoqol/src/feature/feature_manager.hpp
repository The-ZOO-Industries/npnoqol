#pragma once

#include "feature.hpp"
#include "../sdk/net/minecraft/client/minecraft.hpp"

#include "impl/command/command_manager.hpp"

namespace zoo
{
	class feature_manager final
	{
	public:
		feature_manager() noexcept;

		~feature_manager() noexcept;

		auto run_tick() noexcept
			-> void;

	private:
		static auto run_tick_hook(vmhook::return_value& return_value, const std::unique_ptr<sdk::minecraft>& minecraft)
			-> void;

		static auto send_chat_message_hook(vmhook::return_value& return_value, const std::unique_ptr<sdk::entity_player_sp>& player, const std::string& message)
			-> void;

		inline static std::unique_ptr<zoo::command_manager> command_manager{};
	};
}
