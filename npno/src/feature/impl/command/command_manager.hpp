#pragma once

#include "command.hpp"

namespace npno
{
	class command_manager final
	{
	public:
		command_manager();

		~command_manager();

		auto update()
			-> void;

		auto on_chat_message(const std::string& message)
			-> bool;

	private:
		template <typename com>
			requires (std::is_base_of_v<npno::command, com>)
		auto register_command()
			-> void;

		std::vector<std::unique_ptr<npno::command>> commands;

		struct send_chat_message_hook : public npno::hook_handler
		{
			std::string command_name{};
			std::string command_line{};

			auto clear() ->
				void override
			{
				this->detected = false;

				this->command_name = std::string{};
				this->command_line = std::string{};
			}
		};

		send_chat_message_hook hook;
		std::mutex hook_mutex;
	};
}