#pragma once

#include "../module.hpp"

namespace npno
{
	class chat_manager final : public npno::module
	{
	public:
		chat_manager();

		~chat_manager();

		auto update()
			-> void override {};

		auto on_load_world()
			-> void override {};

		auto on_print_chat_message(const std::unique_ptr<jni::i_chat_component>& chat_component)
			-> bool override;

	private:
		std::vector<std::regex> blacklisted_lines;
	};
}