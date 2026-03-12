#include "module_manager.hpp"


npno::module_manager::module_manager()
{
	
}

npno::module_manager::~module_manager() = default;

auto npno::module_manager::update()
	-> void
{
	std::lock_guard<std::mutex> lock{ this->hook_mutex };

	for (const std::unique_ptr<npno::module>& module : this->modules)
	{
		if (module->is_enable() and module->sanity_check())
		{
			module->update();

			if (this->hook.detected)
			{
				module->on_load_world();

				this->hook.clear();
			}
		}
	}
}

auto npno::module_manager::on_load_world()
	-> void
{
	this->hook.detected = true;
}

template <typename mod>
	requires (std::is_base_of_v<npno::module, mod>)
auto npno::module_manager::register_module()
-> void
{
	this->modules .emplace_back(std::make_unique<mod>());
}