#include "command_manager.hpp"

#include "impl/denick.hpp"
#include "impl/find_nick.hpp"
#include "impl/set_apikey.hpp"

zoo::command_manager::command_manager() noexcept
{
	this->register_command<zoo::set_apikey>();
	this->register_command<zoo::denick>();
	this->register_command<zoo::find_nick>();
	this->worker = std::thread{ &zoo::command_manager::worker_loop, this };
}

zoo::command_manager::~command_manager() noexcept
{
	this->running = false;
	this->queue_cv.notify_all();

	if (this->worker.joinable())
	{
		this->worker.join();
	}
}

auto zoo::command_manager::run_tick() noexcept
	-> void
{
	std::lock_guard<std::mutex> lock{ this->hook_mutex };
	this->send_chat_message.clear();
}

auto zoo::command_manager::on_send_chat_message(const std::string& message) noexcept
	-> bool
{
	for (const std::unique_ptr<zoo::command>& command : this->commands)
	{
		if (command->on_send_chat_message(message))
		{
			std::lock_guard<std::mutex> lock{ this->hook_mutex };
			this->send_chat_message.detected = true;
			this->send_chat_message.command_name = command->get_name();
			this->send_chat_message.command_line = message;
			this->queue_command(message);
			return true;
		}
	}

	return false;
}

auto zoo::command_manager::queue_command(const std::string& message) noexcept
	-> void
{
	{
		std::lock_guard<std::mutex> lock{ this->queue_mutex };
		this->queued_commands.push_back(message);
	}
	this->queue_cv.notify_one();
}

template <typename com>
	requires (std::is_base_of_v<zoo::command, com>)
auto zoo::command_manager::register_command()
	-> void
{
	this->commands.emplace_back(std::make_unique<com>());
}

auto zoo::command_manager::worker_loop() noexcept
	-> void
{
	while (this->running)
	{
		std::string command_line{};

		{
			std::unique_lock<std::mutex> lock{ this->queue_mutex };
			this->queue_cv.wait(lock, [this]()
				{
					return !this->running || !this->queued_commands.empty();
				});

			if (!this->running && this->queued_commands.empty())
			{
				return;
			}

			command_line = std::move(this->queued_commands.front());
			this->queued_commands.pop_front();
		}

		this->execute_command(command_line);
	}
}

auto zoo::command_manager::execute_command(const std::string& message) noexcept
	-> void
{
	auto to_lower = [](const std::string& string)
		-> std::string
		{
			std::string lower_string{ string };

			std::transform(lower_string.begin(), lower_string.end(), lower_string.begin(), ::tolower);

			return lower_string;
		};

	for (const std::unique_ptr<zoo::command>& command : this->commands)
	{
		if (command->sanity_check() && command->on_send_chat_message(message))
		{
			command->on_command(command->get_arguments(message));
			return;
		}
	}
}
