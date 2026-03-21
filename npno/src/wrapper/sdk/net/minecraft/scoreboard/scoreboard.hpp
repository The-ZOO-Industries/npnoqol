#pragma once

#include <easy_jni/easy_jni.hpp>

#include "score_player_team.hpp"
#include "score_objective.hpp"
#include "score.hpp"

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
			return get_method<jni::collection>(mapping::scoreboard::getTeams)->call()->to_vector<jni::score_player_team>();
		}

		auto get_team(const std::string& value) const
			-> std::unique_ptr<jni::score_player_team>
		{
			return get_method<jni::score_player_team, std::string>(mapping::scoreboard::getTeam)->call(value);
		}

		auto create_team(const std::string& value) const
			-> std::unique_ptr<jni::score_player_team>
		{
			return get_method<jni::score_player_team, std::string>(mapping::scoreboard::createTeam)->call(value);
		}

		auto remove_player_from_team(const std::string& player_name, const std::unique_ptr<jni::score_player_team>& team) const
			-> void
		{
			get_method<void, std::string, jni::score_player_team>(mapping::scoreboard::removePlayerFromTeam)->call(player_name, team);
		}

		auto remove_team(const std::unique_ptr<jni::score_player_team>& value) const
			-> void
		{
			get_method<void, jni::score_player_team>(mapping::scoreboard::removeTeam)->call(value);
		}

		auto get_players_team(const std::string& value) const
			-> std::unique_ptr<jni::score_player_team>
		{
			return get_method<jni::score_player_team, std::string>(mapping::scoreboard::getPlayersTeam)->call(value);
		}

		auto add_player_to_team(const std::string& player_name, const std::string& team_name) const
			-> bool
		{
			return get_method<bool, std::string, std::string>(mapping::scoreboard::addPlayerToTeam)->call(player_name, team_name);
		}

		auto set_objective_in_display_slot(const int display_slot, const std::unique_ptr<jni::score_objective>& score) const
			-> void
		{
			get_method<void, int, jni::score_objective>(mapping::scoreboard::setObjectiveInDisplaySlot)->call(display_slot, score);
		}

		auto get_objective_in_display_slot(const int display_slot) const
			-> std::unique_ptr<jni::score_objective>
		{
			return get_method<jni::score_objective, int>(mapping::scoreboard::getObjectiveInDisplaySlot)->call(display_slot);
		}

		auto get_score_objectives() const
			-> std::vector<std::unique_ptr<jni::score_objective>>
		{
			return get_method<jni::collection>(mapping::scoreboard::getScoreObjectives)->call()->to_vector<jni::score_objective>();
		}

		auto get_objective(const std::string& value) const
			-> std::unique_ptr<jni::score_objective>
		{
			return get_method<jni::score_objective, std::string>(mapping::scoreboard::getObjective)->call(value);
		}

		auto add_score_objective(const std::string& name, const std::unique_ptr<jni::i_score_objective_criteria>& dummy) const
			-> std::unique_ptr<jni::score_objective>
		{
			return get_method<jni::score_objective, std::string, jni::i_score_objective_criteria>(mapping::scoreboard::addScoreObjective)->call(name, dummy);
		}

		auto get_value_from_objective(const std::string& name, const std::unique_ptr<jni::score_objective>& objective) const
			-> std::unique_ptr<jni::score>
		{
			return get_method<jni::score, std::string, jni::score_objective>(mapping::scoreboard::getValueFromObjective)->call(name, objective);
		}
	};
}