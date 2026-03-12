#include "command_manager.hpp"

#include "impl/set_apikey.hpp"

npno::command_manager::command_manager()
{
	this->register_command<npno::set_apikey>();
}

npno::command_manager::~command_manager() = default;

auto npno::command_manager::update()
	-> void
{
	std::lock_guard<std::mutex> lock{ this->hook_mutex };

	for (const std::unique_ptr<npno::command>& command : this->commands)
	{
		if (this->hook.detected and command->get_name() == this->hook.command_name)
		{
			command->on_command(command->get_arguments(this->hook.command_line));

			this->hook.clear();

			break;
		}
	}
}

auto npno::command_manager::on_chat_message(const std::string& message)
	-> bool
{
	for (const std::unique_ptr<npno::command>& command : this->commands)
	{
		if (command->on_chat_message(message))
		{
			std::lock_guard<std::mutex> lock{ this->hook_mutex };

			this->hook.detected = true;
			this->hook.command_name = command->get_name();
			this->hook.command_line = message;
			
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