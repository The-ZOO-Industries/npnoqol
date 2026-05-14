#pragma once

#include "feature.hpp"
#include "../sdk/net/minecraft/client/minecraft.hpp"
#include "../sdk/net/minecraft/client/gui/gui_new_chat.hpp"
#include "../sdk/net/minecraft/client/multiplayer/world_client.hpp"

#include "impl/command/command_manager.hpp"
#include "impl/module/module_manager.hpp"

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

		static auto print_chat_message_hook(vmhook::return_value& return_value, const std::unique_ptr<sdk::gui_new_chat>& gui_new_chat, const std::unique_ptr<sdk::i_chat_component>& chat_component)
			-> void;

		static auto load_world_hook(vmhook::return_value& return_value, const std::unique_ptr<sdk::minecraft>& minecraft)
			-> void;

		inline static std::unique_ptr<zoo::command_manager> command_manager{};
		inline static std::unique_ptr<zoo::module_manager> module_manager{};
	};
}
