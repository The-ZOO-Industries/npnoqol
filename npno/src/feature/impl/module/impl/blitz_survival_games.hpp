#pragma once

#include "../hypixel_gametype_module.hpp"

namespace npno
{
	class blitz_survival_games final : public npno::hypixel_gametype_module
	{
	public:
		blitz_survival_games();

		~blitz_survival_games();

		auto update()
			-> void override;

		auto on_print_chat_message(const std::unique_ptr<jni::i_chat_component>& chat_component)
			-> bool override;

		auto load_players_datas(const std::vector<std::string>& player_names)
			-> void override;

	private:
		enum class mode : std::int8_t
		{
			SOLO,
			TEAMS,
			LOBBY
		};

		auto handle_mode() 
			-> void override;

		auto format_tab_name(const std::unique_ptr<jni::entity_player>& player) 
			-> std::string override;
		auto format_nametag(const std::unique_ptr<jni::entity_player>& player) 
			-> std::pair<std::string, std::string> override;

		auto get_wins_color(const std::string& wins) const 
			-> std::string;
		auto get_kdr_color(const std::string& kdr) const 
			-> std::string;

		auto assign_team_colors() 
			-> void;

		std::unordered_map<std::string, std::string> team_colors;
		std::uint32_t next_color_index{ 0 };

		mode mode;
	};
}