#include "command_manager.hpp"

#include "impl/set_apikey.hpp"

npno::command_manager::command_manager()
{
	this->register_command<npno::set_apikey>();
}

npno::command_manager::~command_manager() = default;

auto npno::command_manager::update(const std::string& message) const
	-> bool
{
	for (const std::unique_ptr<npno::command>& command : this->commands)
	{
		if (command->on_chat_message(message))
		{
			return true;
		}
	}

	return false;
}

template <typename com>
	requires (std::is_base_of_v<npno::command, com>)
auto npno::command_manager::register_command()
	-> void
{
	this->commands.emplace_back(std::make_unique<com>());
}