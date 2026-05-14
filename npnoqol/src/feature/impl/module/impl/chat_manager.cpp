#include "chat_manager.hpp"

#include "../../../../util/enum_chat_formatting.hpp"

zoo::chat_manager::chat_manager() noexcept = default;

zoo::chat_manager::~chat_manager() noexcept = default;

auto zoo::chat_manager::on_run_tick() noexcept
	-> void
{

}

auto zoo::chat_manager::on_print_chat_message(vmhook::return_value& return_value, const std::unique_ptr<sdk::i_chat_component>& chat_component) noexcept
	-> bool
{
	if (!chat_component || !chat_component->get_instance())
	{
		return false;
	}

	std::string line{ chat_component->get_formatted_text() };
	if (!line.contains(enum_chat_formatting::obfuscated))
	{
		return false;
	}

	std::size_t pos{};
	while ((pos = line.find(enum_chat_formatting::obfuscated)) != std::string::npos)
	{
		line.erase(pos, enum_chat_formatting::obfuscated.length());
	}

	return_value.set_arg(1, vmhook::make_unique<sdk::chat_component_text>(line));

	return false;
}
