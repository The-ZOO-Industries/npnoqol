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
		auto watchdog_lover(const std::string& text) const
			-> void;

		auto auto_gg(const std::string& text) const
			-> void;

		auto welcome_guild(const std::string& text) const
			-> void;

		auto boop_friend(const std::string& text) const
			-> void;

		auto random_case(const std::string& text) const
			-> std::string;

		std::vector<std::regex> blacklisted_lines;
		std::vector<std::regex> auto_gg_lines;
	};
}