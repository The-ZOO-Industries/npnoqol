#include "module.hpp"

zoo::module::module() noexcept = default;

zoo::module::~module() noexcept = default;

auto zoo::module::on_load_world(const std::unique_ptr<sdk::minecraft>& minecraft) noexcept
	-> void
{

}

auto zoo::module::on_minecraft_tick() noexcept
	-> void
{

}

auto zoo::module::on_print_chat_message(vmhook::return_value& return_value, const std::unique_ptr<sdk::i_chat_component>& chat_component) noexcept
	-> bool
{
	return false;
}
