#pragma once

#include "../module.hpp"

#include <atomic>
#include <chrono>
#include <mutex>
#include <string>
#include <vector>

namespace zoo
{
	class gametype_manager final : public zoo::module
	{
	public:
		gametype_manager() noexcept;

		~gametype_manager() noexcept;

		auto on_run_tick() noexcept
			-> void override;

		auto on_minecraft_tick() noexcept
			-> void override;

		auto on_print_chat_message(vmhook::return_value& return_value, const std::unique_ptr<sdk::i_chat_component>& chat_component) noexcept
			-> bool override;

		auto on_load_world(const std::unique_ptr<sdk::minecraft>& minecraft) noexcept
			-> void override;

	private:
		auto extract_json(const std::string& line) const noexcept
			-> std::string;

		static auto check_api_keys() noexcept
			-> std::vector<std::string>;

		auto queue_chat_messages(std::vector<std::string>&& messages) noexcept
			-> void;

		std::mutex load_world_mutex{};
		std::mutex chat_messages_mutex{};
		std::vector<std::string> queued_chat_messages{};
		std::chrono::steady_clock::time_point last_load_world{};
		std::atomic_bool locraw_queued{};
		std::atomic_bool api_check_running{};
		std::atomic<std::int64_t> next_locraw_chat_ms{};
	};
}
