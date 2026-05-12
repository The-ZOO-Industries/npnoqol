#include "feature_manager.hpp"

zoo::feature_manager::feature_manager() noexcept
{
	command_manager = std::make_unique<zoo::command_manager>();

	vmhook::hook<sdk::minecraft>(mapping::minecraft::runTick, &zoo::feature_manager::run_tick_hook);
	vmhook::hook<sdk::entity_player_sp>(mapping::entity_player_sp::sendChatMessage, &zoo::feature_manager::send_chat_message_hook);
}

zoo::feature_manager::~feature_manager() noexcept
{
	vmhook::shutdown_hooks();
	command_manager.reset();
}

auto zoo::feature_manager::run_tick() noexcept
	-> void
{
	command_manager->run_tick();
}

auto zoo::feature_manager::run_tick_hook(vmhook::return_value& return_value, const std::unique_ptr<sdk::minecraft>& thizz)
	-> void
{
	command_manager->run_tick();
}

auto zoo::feature_manager::send_chat_message_hook(vmhook::return_value& return_value, const std::unique_ptr<sdk::entity_player_sp>& thizz, const std::string& message)
	-> void
{
	if (command_manager->on_send_chat_message(message))
	{
		return_value.cancel();
	}
}