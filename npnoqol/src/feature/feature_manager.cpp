#include "feature_manager.hpp"

zoo::feature_manager::feature_manager() noexcept
{
	command_manager = std::make_unique<zoo::command_manager>();
	module_manager = std::make_unique<zoo::module_manager>();

	vmhook::hook<sdk::minecraft>(mapping::minecraft::runTick, &zoo::feature_manager::run_tick_hook);
	vmhook::hook<sdk::entity_player_sp>(mapping::entity_player_sp::sendChatMessage, &zoo::feature_manager::send_chat_message_hook);
	vmhook::hook<sdk::gui_new_chat>(mapping::gui_new_chat::printChatMessage, &zoo::feature_manager::print_chat_message_hook);
	vmhook::hook<sdk::minecraft>(mapping::minecraft::loadWorld, &zoo::feature_manager::load_world_hook);
}

zoo::feature_manager::~feature_manager() noexcept
{
	vmhook::shutdown_hooks();
	module_manager.reset();
	command_manager.reset();
}

auto zoo::feature_manager::run_tick() noexcept
	-> void
{
	command_manager->run_tick();
	module_manager->run_tick(sdk::minecraft::get_minecraft());
}

auto zoo::feature_manager::run_tick_hook(vmhook::return_value& return_value, const std::unique_ptr<sdk::minecraft>& thizz)
	-> void
{
	module_manager->run_tick(thizz);
}

auto zoo::feature_manager::send_chat_message_hook(vmhook::return_value& return_value, const std::unique_ptr<sdk::entity_player_sp>& thizz, const std::string& message)
	-> void
{
	if (command_manager->on_send_chat_message(thizz, message))
	{
		return_value.cancel();
	}
}

auto zoo::feature_manager::print_chat_message_hook(vmhook::return_value& return_value, const std::unique_ptr<sdk::gui_new_chat>& thizz, const std::unique_ptr<sdk::i_chat_component>& chat_component)
	-> void
{
	if (module_manager->on_print_chat_message(return_value, thizz, chat_component))
	{
		return_value.cancel();
	}
}

auto zoo::feature_manager::load_world_hook(vmhook::return_value& return_value, const std::unique_ptr<sdk::minecraft>& thizz)
	-> void
{
	module_manager->on_load_world(thizz);
}
