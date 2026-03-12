#pragma once

#include "module.hpp"

namespace npno
{
	class module_manager final
	{
	public:
		module_manager();

		~module_manager();

		auto update()
			-> void;

		auto on_load_world()
			-> void;

		auto on_print_chat_message(const std::unique_ptr<jni::i_chat_component>& chat_component)
			-> bool;

	private:
		template <typename mod>
			requires (std::is_base_of_v<npno::module, mod>)
		auto register_module()
			-> void;

		std::vector<std::unique_ptr<npno::module>> modules;

		struct load_world_hook : public npno::hook_handler
		{
			
		};

		load_world_hook load_world;

		std::mutex hook_mutex;
	};
}