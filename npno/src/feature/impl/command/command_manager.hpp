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

		struct hook_handler
		{
			bool detected{ false };

			std::string command_name{};
			std::string command_line{};

			auto clear() ->
				void
			{
				this->detected = false;

				this->command_name = std::string{};
				this->command_line = std::string{};
			}
		};

		hook_handler hook;
		std::mutex hook_mutex;
	};
}