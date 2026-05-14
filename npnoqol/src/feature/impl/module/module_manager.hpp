#pragma once

#include "module.hpp"

#include <memory>
#include <type_traits>
#include <vector>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

namespace zoo
{
	class module_manager final
	{
	public:
		module_manager() noexcept;

		~module_manager() noexcept;

		auto run_tick(const std::unique_ptr<sdk::minecraft>& minecraft) noexcept
			-> void;

		auto on_load_world(const std::unique_ptr<sdk::minecraft>& minecraft) noexcept
			-> void;

		auto on_print_chat_message(vmhook::return_value& return_value, const std::unique_ptr<sdk::gui_new_chat>& gui_new_chat, const std::unique_ptr<sdk::i_chat_component>& chat_component) noexcept
			-> bool;

	private:
		template <typename mod>
			requires (std::is_base_of_v<zoo::module, mod>)
		auto register_module()
			-> void;

		auto worker_loop() noexcept
			-> void;

		auto process_run_tick() noexcept
			-> void;

		auto process_minecraft_tick() noexcept
			-> void;

		auto process_load_world() noexcept
			-> void;

		std::vector<std::unique_ptr<zoo::module>> modules;
		std::mutex worker_mutex{};
		std::condition_variable worker_cv{};
		std::thread worker{};
		std::atomic_size_t queued_ticks{};
		std::atomic_bool load_world_queued{};
		std::atomic<std::int64_t> next_load_world_ms{};
		std::atomic_bool running{ true };
	};
}
