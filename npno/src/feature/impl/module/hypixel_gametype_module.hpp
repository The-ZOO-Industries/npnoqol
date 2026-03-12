#pragma once

#include "module.hpp"

namespace npno
{
	class hypixel_gametype_module : public npno::module
	{
	public:
		explicit hypixel_gametype_module(const hypixel_gametype::gametype gametype = hypixel_gametype::gametype::LOBBY);

		virtual ~hypixel_gametype_module();

		auto on_load_world()
			-> void override;

		virtual auto on_print_chat_message(const std::unique_ptr<jni::i_chat_component>& chat_component)
			-> bool override { return false; };

		auto get_gametype() const
			-> hypixel_gametype::gametype;

	private:
		struct player_data 
		{
			std::string name{};
		};

		std::unordered_map<std::string, player_data> player_cache;

		hypixel_gametype::gametype gametype;
	};
}