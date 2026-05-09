#pragma once

#include "command.hpp"

#include <string>
#include <mutex>
#include <vector>
#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <deque>
#include <thread>

namespace zoo
{
	struct send_chat_message_hook : public zoo::hook_handler
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

	class command_manager final
	{
	public:
		command_manager() noexcept;

		~command_manager() noexcept;

		auto run_tick() noexcept
			-> void;

		auto on_send_chat_message(const std::string& message) noexcept
			-> bool;

		auto queue_command(const std::string& message) noexcept
			-> void;

	private:
		template <typename com>
			requires (std::is_base_of_v<zoo::command, com>)
		auto register_command()
			-> void;

		auto worker_loop() noexcept
			-> void;

		auto execute_command(const std::string& message) noexcept
			-> void;

		std::vector<std::unique_ptr<zoo::command>> commands;
		zoo::send_chat_message_hook send_chat_message{};
		std::mutex hook_mutex{};
		std::mutex queue_mutex{};
		std::condition_variable queue_cv{};
		std::deque<std::string> queued_commands{};
		std::thread worker{};
		std::atomic_bool running{ true };
	};
}
