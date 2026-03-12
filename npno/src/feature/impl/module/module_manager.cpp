#include "module_manager.hpp"

#include "hypixel_gametype_module.hpp"

#include "impl/blitz_survival_games.hpp"
#include "impl/gametype_manager.hpp"

npno::module_manager::module_manager()
{
	this->register_module<npno::blitz_survival_games>();
	this->register_module<npno::gametype_manager>();
}

npno::module_manager::~module_manager() = default;

auto npno::module_manager::update()
	-> void
{
	std::lock_guard<std::mutex> lock{ this->hook_mutex };

	for (const std::unique_ptr<npno::module>& module : this->modules)
	{
		if (auto* hypixel_module = dynamic_cast<npno::hypixel_gametype_module*>(module.get()))
		{
			hypixel_module->set_enable(hypixel_module->get_gametype() == hypixel_gametype::current_gametype);
		}

		if (module->is_enable() and module->sanity_check())
		{
			module->update();

			if (this->load_world.detected)
			{
				module->on_load_world();

				this->load_world.clear();
			}
		}
	}
}

auto npno::module_manager::on_load_world()
	-> void
{
	this->load_world.detected = true;
}

auto npno::module_manager::on_print_chat_message(const std::unique_ptr<jni::i_chat_component>& chat_component)
-> bool
{
	bool result{ false };
	for (const std::unique_ptr<npno::module>& module : this->modules)
	{
		if (module->is_enable() and module->sanity_check() and module->on_print_chat_message(chat_component))
		{
			result = true;
		}
	}

	return result;
}

template <typename mod>
	requires (std::is_base_of_v<npno::module, mod>)
auto npno::module_manager::register_module()
-> void
{
	this->modules .emplace_back(std::make_unique<mod>());
}