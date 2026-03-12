#include "hypixel_gametype_module.hpp"

npno::hypixel_gametype_module::hypixel_gametype_module(const hypixel_gametype::gametype gametype)
	: npno::module{ false }
	, gametype{ gametype }
{

}

npno::hypixel_gametype_module::~hypixel_gametype_module() = default;\

auto npno::hypixel_gametype_module::on_load_world()
	-> void
{
	hypixel_gametype::current_gametype = hypixel_gametype::gametype::LOBBY;

	this->player_cache.clear();
	this->team_manager.clear();
	this->sorted_teams.clear();
}

auto npno::hypixel_gametype_module::get_gametype() const
	-> hypixel_gametype::gametype
{
	return this->gametype;
}

auto npno::hypixel_gametype_module::update_tab_list()
	-> void
{
	const std::unique_ptr<jni::entity_player_sp>& the_player{ mc->get_the_player() };
	const std::unique_ptr<jni::world_client>& the_world{ mc->get_the_world() };
	const std::vector<std::unique_ptr<jni::network_player_info>>& player_info_map{ the_player->get_send_queue()->get_player_info_map() };

	for (std::size_t i{ 0 }; i < player_info_map.size(); ++i)
	{
		const std::unique_ptr<jni::entity_player>& player_entity{ the_world->get_player_entity_by_name(player_info_map[i]->get_game_profile()->get_name()) };

		if (player_entity->get_instance())
		{
			if (this->is_bot(player_entity))
			{
				continue;
			}

			player_info_map[i]->set_display_name(std::make_unique<jni::chat_component_text>(this->format_tab_name(player_entity)));
		}
	}
}

auto npno::hypixel_gametype_module::update_nametags() 
	-> void
{
	this->fill_team_manager();
	this->orginize_teams();
	this->assign_npno_teams();
	this->apply_teams();
}

auto npno::hypixel_gametype_module::get_player_data(const std::string& player_name) 
	-> player_data
{
	if (auto it = this->player_cache.find(player_name); it != this->player_cache.end())
	{
		return it->second;
	}

	player_data playerData{};
	playerData.error = true;

	return playerData;
}

auto npno::hypixel_gametype_module::get_hp_color(const float hp) const 
	-> std::string
{
	if (hp >= 20.0f) return enum_chat_formatting::dark_green;
	if (hp >= 10.0f) return enum_chat_formatting::green;
	if (hp >= 5.0f)  return enum_chat_formatting::yellow;
	return enum_chat_formatting::red;
}

auto npno::hypixel_gametype_module::orginize_teams() 
	-> void
{
	this->sorted_teams.clear();

	for (const auto& [player_name, team] : this->team_manager)
	{
		if (!team.hypixel_team.empty())
		{
			this->sorted_teams[team].push_back(player_name);
		}
	}
}

auto npno::hypixel_gametype_module::fill_team_manager() -> void
{
	const std::unique_ptr<jni::world_client> the_world{ mc->get_the_world() };
	const std::unique_ptr<jni::scoreboard> scoreboard{ the_world->get_scoreboard() };

	for (const std::unique_ptr<ScorePlayerTeam>& scoreTeam : scoreboard->get_teams())
	{
		const std::string hypixelTeamName{ scoreTeam->GetTeamName() };

		for (const std::string& playerName : scoreTeam->GetMembershipCollection())
		{
			if (!theWorld->GetPlayerEntityByName(playerName)->GetInstance())
			{
				continue;
			}

			if (this->IsBot(theWorld->GetPlayerEntityByName(playerName)))
			{
				continue;
			}

			if (!hypixelTeamName.starts_with("npno_"))
			{
				auto it = this->teamManager.find(playerName);
				if (it == this->teamManager.end())
				{
					Team team{};
					team.hypixelTeam = hypixelTeamName;
					this->teamManager.insert({ playerName, std::move(team) });
				}
				else if (it->second.hypixelTeam != hypixelTeamName)
				{
					it->second.hypixelTeam = hypixelTeamName;
					it->second.npnoTeam.clear();
				}
			}
		}
	}
}