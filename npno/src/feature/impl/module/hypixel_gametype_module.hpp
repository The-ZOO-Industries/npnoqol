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

	protected:
		struct player_data 
		{
			std::string prefix{};
			std::string rank{};
			std::string suffix{};

			bool is_nicked{ false };
			bool error{ false };
		};

		struct team
		{
			std::vector<std::string> players{};
			std::string hypixel_team{};
			std::string npno_team{};

			auto operator<(const team& other) const 
				-> bool
			{
				return hypixel_team < other.hypixel_team;
			}

			auto operator==(const team& other) const 
				-> bool
			{
				return hypixel_team == other.hypixel_team;
			}
		};

		auto update_tab_list() 
			-> void;
		auto update_nametags() 
			-> void;
		auto update_second_nametags()
			-> void;

		virtual auto get_player_data(const std::string& player_name) 
			-> player_data;

		virtual auto load_players_datas(const std::vector<std::string>& player_names) 
			-> void = 0;

		virtual auto format_tab_name(const std::unique_ptr<jni::entity_player>& player) 
			-> std::string = 0;
		virtual auto format_nametag(const std::unique_ptr<jni::entity_player>& player) 
			-> std::pair<std::string, std::string> = 0;
		virtual auto format_second_nametag(const std::unique_ptr<jni::entity_player>& player)
			-> std::string = 0;

		virtual auto get_hp_color(const float hp) const 
			-> std::string;

		virtual auto handle_mode() 
			-> void = 0;

		std::map<team, std::vector<std::string>> sorted_teams;
		std::unordered_map<std::string, team> team_manager;

		std::unordered_map<std::string, player_data> player_archive_cache;
		std::unordered_map<std::string, player_data> player_cache;

		mutable std::mutex player_cache_mutex;

		hypixel_gametype::gametype gametype;

	private:
		auto orginize_teams() 
			-> void;
		auto fill_team_manager() 
			-> void;
		auto assign_npno_teams() 
			-> void;
		auto apply_teams()
			-> void;

		auto load_players()
			-> void;
		auto archive_player_cache()
			-> void;
	};
}