#pragma once

#include <easy_jni/easy_jni.hpp>

#include "score_player_team.hpp"

namespace jni
{
	class scoreboard final : public jni::object
	{
	public:
		explicit scoreboard(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto get_teams() const
			-> std::vector<std::unique_ptr<jni::score_player_team>>
		{
			return get_method<jni::collection>("getTeams")->call()->to_vector<jni::score_player_team>();
		}

		auto get_team(const std::string& value) const
			-> std::unique_ptr<jni::score_player_team>
		{
			return get_method<jni::score_player_team, std::string>("getTeam")->call(value);
		}

		auto create_team(const std::string& value) const
			-> std::unique_ptr<jni::score_player_team>
		{
			return get_method<jni::score_player_team, std::string>("createTeam")->call(value);
		}

		auto remove_player_from_team(const std::string& player_name, const std::unique_ptr<jni::score_player_team>& team) const
			-> void
		{
			get_method<void, std::string, jni::score_player_team>("removePlayerFromTeam")->call(player_name, team);
		}

		auto remove_team(const std::unique_ptr<jni::score_player_team>& value) const
			-> void
		{
			get_method<void, jni::score_player_team>("removeTeam")->call(value);
		}

		auto get_players_team(const std::string& value) const
			-> std::unique_ptr<jni::score_player_team>
		{
			return get_method<jni::score_player_team, std::string>("getPlayersTeam")->call(value);
		}

		auto add_player_to_team(const std::string& player_name, const std::string& team_name) const
			-> bool
		{
			return get_method<bool, std::string, std::string>("addPlayerToTeam")->call(player_name, team_name);
		}
	};
}