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
	this->longest.clear();
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

			player_info_map[i]->set_display_name(jni::make_unique<jni::chat_component_text,std::string>(this->format_tab_name(player_entity)));
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

	this->load_players();
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

auto npno::hypixel_gametype_module::fill_team_manager() 
	-> void
{
	const std::unique_ptr<jni::world_client> the_world{ mc->get_the_world() };
	const std::unique_ptr<jni::scoreboard> scoreboard{ the_world->get_scoreboard() };

	for (const std::unique_ptr<jni::score_player_team>& score_team : scoreboard->get_teams())
	{
		const std::string hypixel_team_name{ score_team->get_team_name() };

		for (const std::string& player_name : score_team->get_membership_collection())
		{
			if (!the_world->get_player_entity_by_name(player_name)->get_instance())
			{
				continue;
			}

			if (this->is_bot(the_world->get_player_entity_by_name(player_name)))
			{
				continue;
			}

			if (!hypixel_team_name.starts_with("npno_"))
			{
				auto it = this->team_manager.find(player_name);
				if (it == this->team_manager.end())
				{
					team team{};
					team.hypixel_team = hypixel_team_name;
					this->team_manager.insert({ player_name, std::move(team) });
				}
				else if (it->second.hypixel_team != hypixel_team_name)
				{
					it->second.hypixel_team = hypixel_team_name;
					it->second.npno_team.clear();
				}
			}
		}
	}
}

auto npno::hypixel_gametype_module::assign_npno_teams() 
	-> void
{
	std::int32_t teamCounter{ 0 };
	for (auto& [team, players] : this->sorted_teams)
	{
		for (std::string& player_name : players)
		{
			if (hypixel_gametype_module::team& player_team{ this->team_manager[player_name] }; player_team.npno_team.empty())
			{
				player_team.npno_team = std::format("npno_{}", teamCounter);
			}
		}
		++teamCounter;
	}
}

auto npno::hypixel_gametype_module::apply_teams() 
	-> void
{
	const std::unique_ptr<jni::world_client> the_world{ mc->get_the_world() };
	const std::unique_ptr<jni::scoreboard> scoreboard{ the_world->get_scoreboard() };

	for (const auto& [player_name, player_team] : this->team_manager)
	{
		if (player_team.npno_team.empty())
		{
			continue;
		}

		std::unique_ptr<jni::score_player_team> team{ scoreboard->get_team(player_team.npno_team) };
		if (!team->get_instance())
		{
			team = scoreboard->create_team(player_team.npno_team);
		}

		std::unique_ptr<jni::score_player_team> current_team{ scoreboard->get_team(player_name) };
		if (current_team->get_instance() and not current_team->get_team_name().starts_with("npno_"))
		{
			scoreboard->remove_player_from_team(player_name, current_team);
		}

		if (not scoreboard->get_players_team(player_name) or scoreboard->get_players_team(player_name)->get_team_name() != player_team.npno_team)
		{
			scoreboard->add_player_to_team(player_name, player_team.npno_team);
		}

		if (const std::unique_ptr<jni::entity_player>& player{ the_world->get_player_entity_by_name(player_name) }; 
			player->get_instance() and not this->is_bot(player))
		{
			const std::pair<std::string, std::string> nametag{ this->format_nametag(player) };
			team->set_name_prefix(nametag.first);
			team->set_name_suffix(nametag.second);
		}
	}
}

auto npno::hypixel_gametype_module::load_players()
	-> void
{
	std::vector<std::string> to_fetch{};
	for (const auto& [player_name, _] : this->team_manager)
	{
		if (this->player_cache.find(player_name) == this->player_cache.end())
		{
			to_fetch.push_back(player_name);
		}
	}

	if (!to_fetch.empty())
	{
		for (const std::string& name : to_fetch)
		{
			player_data pending{};
			pending.error = true;
			this->player_cache[name] = pending;
		}

		std::thread([this, to_fetch = std::move(to_fetch)]()
			{
				this->load_players_datas(to_fetch);
			}).detach();
	}
}