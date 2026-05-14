#include "module_manager.hpp"

#include "impl/chat_manager.hpp"
#include "impl/gametype_manager.hpp"

zoo::module_manager::module_manager() noexcept
{
	this->register_module<zoo::gametype_manager>();
	this->register_module<zoo::chat_manager>();
	this->worker = std::thread{ &zoo::module_manager::worker_loop, this };
}

zoo::module_manager::~module_manager() noexcept
{
	this->running = false;
	this->worker_cv.notify_all();

	if (this->worker.joinable())
	{
		this->worker.join();
	}
}

auto zoo::module_manager::run_tick(const std::unique_ptr<sdk::minecraft>& minecraft) noexcept
	-> void
{
	this->process_minecraft_tick();
	this->queued_ticks.fetch_add(1, std::memory_order_relaxed);
	this->worker_cv.notify_one();
}

auto zoo::module_manager::on_load_world(const std::unique_ptr<sdk::minecraft>& minecraft) noexcept
	-> void
{
	const std::int64_t now{ std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::steady_clock::now().time_since_epoch()).count() };

	std::int64_t next_allowed{ this->next_load_world_ms.load(std::memory_order_relaxed) };
	while (now >= next_allowed)
	{
		if (this->next_load_world_ms.compare_exchange_weak(next_allowed, now + 3000, std::memory_order_acq_rel))
		{
			this->load_world_queued.store(true, std::memory_order_release);
			this->worker_cv.notify_one();
			return;
		}
	}

	if (now < next_allowed)
	{
		return;
	}

	this->load_world_queued.store(true, std::memory_order_release);
	this->worker_cv.notify_one();
}

auto zoo::module_manager::on_print_chat_message(vmhook::return_value& return_value, const std::unique_ptr<sdk::gui_new_chat>& gui_new_chat, const std::unique_ptr<sdk::i_chat_component>& chat_component) noexcept
	-> bool
{
	bool handled{ false };

	for (const std::unique_ptr<zoo::module>& module : this->modules)
	{
		if (module->on_print_chat_message(return_value, chat_component))
		{
			handled = true;
		}
	}

	return handled;
}

auto zoo::module_manager::worker_loop() noexcept
	-> void
{
	while (this->running)
	{
		{
			std::unique_lock<std::mutex> lock{ this->worker_mutex };
			this->worker_cv.wait(lock, [this]()
				{
					return !this->running
						|| this->queued_ticks.load(std::memory_order_relaxed) != 0
						|| this->load_world_queued.load(std::memory_order_acquire);
				});
		}

		const std::size_t ticks{ this->queued_ticks.exchange(0, std::memory_order_relaxed) };
		for (std::size_t i{}; i < ticks; ++i)
		{
			this->process_run_tick();
		}

		if (this->load_world_queued.exchange(false, std::memory_order_acq_rel))
		{
			this->process_load_world();
		}
	}
}

auto zoo::module_manager::process_run_tick() noexcept
	-> void
{
	for (const std::unique_ptr<zoo::module>& module : this->modules)
	{
		module->on_run_tick();
	}
}

auto zoo::module_manager::process_minecraft_tick() noexcept
	-> void
{
	for (const std::unique_ptr<zoo::module>& module : this->modules)
	{
		module->on_minecraft_tick();
	}
}

auto zoo::module_manager::process_load_world() noexcept
	-> void
{
	for (const std::unique_ptr<zoo::module>& module : this->modules)
	{
		module->on_load_world(nullptr);
	}
}

template <typename mod>
	requires (std::is_base_of_v<zoo::module, mod>)
auto zoo::module_manager::register_module()
	-> void
{
	this->modules.emplace_back(std::make_unique<mod>());
}
