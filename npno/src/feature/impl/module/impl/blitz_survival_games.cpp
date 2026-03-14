#include "blitz_survival_games.hpp"

npno::blitz_survival_games::blitz_survival_games()
	: npno::hypixel_gametype_module{ hypixel_gametype::gametype::BLITZSURVIVALGAMES }
    , mode{ mode::LOBBY }
{

}

npno::blitz_survival_games::~blitz_survival_games() = default;

auto npno::blitz_survival_games::update()
	-> void
{
	this->handle_mode();
	if (this->mode == mode::LOBBY)
	{
		return;
	}

    this->update_nametags();
    this->update_second_nametags();
    this->assign_team_colors();
    this->update_tab_list();
}

auto npno::blitz_survival_games::on_print_chat_message(const std::unique_ptr<jni::i_chat_component>& chat_component)
	-> bool
{
	if (std::string line{ chat_component->get_formatted_text() }; line.contains(enum_chat_formatting::obfuscated))
	{
		std::size_t pos{};
		while ((pos = line.find(enum_chat_formatting::obfuscated)) != std::string::npos)
		{
			line.erase(pos, 3);
		}

		mc->get_the_player()->add_chat_message(jni::make_unique<jni::chat_component_text>(line));

		return true;
	}

	return false;
}

auto npno::blitz_survival_games::load_players_datas(const std::vector<std::string>& player_names) 
    -> void
{
    const std::vector<nlohmann::json>& responses{ hypixel_api::get_players_stats(player_names) };

    for (std::size_t i{ 0 }; i < player_names.size(); ++i)
    {
        const std::string& player_name{ player_names[i] };
        const nlohmann::json& response{ responses[i] };
        player_data player_data{};

        try
        {
            if (hypixel_api::is_nicked(response))
            {
                player_data.prefix = std::format("{}[NICK]{}", enum_chat_formatting::red, enum_chat_formatting::white);
                player_data.is_nicked = true;

                {
                    std::lock_guard lock{ this->player_cache_mutex };
                    this->player_cache[player_name] = player_data;
                }
                continue;
            }

            player_data.rank = hypixel_api::get_rank_prefix(response);
            const auto& hg{ response.at("player").at("stats").at("HungerGames") };
            const std::int32_t wins{ hg.value("wins", 0) + hg.value("wins_teams", 0) };
            const std::int32_t kills{ hg.value("kills", 0) };
            const std::int32_t deaths{ hg.value("deaths", 0) };

            player_data.prefix = std::format("{}", wins);
            player_data.suffix = std::format("{:.1f}", static_cast<float>(kills) / max(1, deaths));

            {
                std::lock_guard lock{ this->player_cache_mutex };
                this->player_cache[player_name] = player_data;
            }
        }
        catch (...)
        {
            {
                std::lock_guard lock{ this->player_cache_mutex };
                this->player_cache[player_name] = player_data;
            }
        }
    }
}

auto npno::blitz_survival_games::handle_mode() 
    -> void
{
    const std::string currentMode{ hypixel_mode::current_mode };

    if (currentMode == "solo_normal")
    {
        this->mode = mode::SOLO;
    }
    else if (currentMode == "teams_normal")
    {
        this->mode = mode::TEAMS;
    }
    else
    {
        this->mode = mode::LOBBY;
    }
}

auto npno::blitz_survival_games::format_tab_name(const std::unique_ptr<jni::entity_player>& player)
    -> std::string
{
    for (const std::unique_ptr<jni::potion_effect>& effect : player->get_active_potion_effects())
    {
        if (effect->get_effect_name() == "potion.invisibility" and effect->get_duration() > 6000)
        {
            if (this->mode == mode::TEAMS)
            {
                const std::string team_name{ team_manager[player->get_name()].hypixel_team };
                const auto it{ this->team_colors.find(team_name) };
                if (it != this->team_colors.end() and team_colors.size() != 1)
                {
                    return std::format("{}{}", it->second, player->get_name());
                }
            }

            return std::format(" {}{}",
                enum_chat_formatting::dark_aqua,
                player->get_name()
            );
        }
    }

    const player_data player_data{ this->get_player_data(player->get_name()) };
    const float health{ player->get_health() + player->get_absorption_amount() };

    std::string team_prefix{};
    if (this->mode == mode::TEAMS)
    {
        const std::string team_name{ team_manager[player->get_name()].hypixel_team };
        const auto it{ this->team_colors.find(team_name) };
        if (it != this->team_colors.end() and team_colors.size() != 1)
        {
            team_prefix = std::format("{}{}O{} ",
                it->second,
                enum_chat_formatting::obfuscated,
                enum_chat_formatting::reset
            );
        }
    }

    if (player_data.error)
    {
        return std::format(" {}{}? {}{}",
            team_prefix,
            enum_chat_formatting::dark_red,
            enum_chat_formatting::dark_aqua,
            player->get_name()
        );
    }

    if (player_data.is_nicked)
    {
        return std::format(" {}{} {}",
            team_prefix,
            player_data.prefix,
            player->get_name()
        );
    }

    const std::string rank_section{ player_data.rank.empty() ? enum_chat_formatting::gray : (player_data.rank + " ") };

    if (player_data.prefix.empty() or player_data.prefix.empty())
    {
        std::println("[WARNING] format_tab_name() bad error handling for {}, prefix: {}, suffix: {}", 
            player->get_name(), player_data.prefix, player_data.prefix
        );

        return std::format(" {}{}? {}{}",
            team_prefix,
            enum_chat_formatting::dark_red,
            enum_chat_formatting::dark_aqua,
            player->get_name()
        );
    }

    return std::format(" {}{}[{}] {}{} {}{}",
        team_prefix,
        this->get_wins_color(player_data.prefix),
        player_data.prefix,
        rank_section,
        player->get_name(),
        this->get_kdr_color(player_data.suffix),
        player_data.suffix
    );
}

auto npno::blitz_survival_games::format_nametag(const std::unique_ptr<jni::entity_player>& player)
    -> std::pair<std::string, std::string>
{
    const player_data player_data{ this->get_player_data(player->get_name()) };
    const float health{ player->get_health() + player->get_absorption_amount() };

    std::string prefix{ enum_chat_formatting::dark_aqua };
    std::string suffix{};

    if (this->mode == mode::TEAMS)
    {
        const std::string team_name{ this->team_manager[player->get_name()].hypixel_team };
        const auto it{ this->team_colors.find(team_name) };
        if (it != this->team_colors.end())
        {
            prefix += it->second;
        }
    }

    suffix = std::format(" {}{:.1f}", this->get_hp_color(health), health);
   
    return { prefix, suffix };
}

auto npno::blitz_survival_games::format_second_nametag(const std::unique_ptr<jni::entity_player>& player)
    -> std::string
{
    return std::string{};
}

auto npno::blitz_survival_games::get_wins_color(const std::string& wins) const 
    -> std::string
{
    if (wins.empty() or !std::all_of(wins.begin(), wins.end(), ::isdigit)) return enum_chat_formatting::gray;

    const std::int32_t wins_value{ std::stoi(wins) };

    if (wins_value >= 2500) return enum_chat_formatting::dark_red;
    if (wins_value >= 1000) return enum_chat_formatting::red;
    if (wins_value >= 500) return enum_chat_formatting::gold;
    if (wins_value >= 200) return enum_chat_formatting::dark_green;
    if (wins_value >= 100) return enum_chat_formatting::green;
    return enum_chat_formatting::gray;
}

auto npno::blitz_survival_games::get_kdr_color(const std::string& kdr) const 
    -> std::string
{
    if (kdr.empty()) return enum_chat_formatting::gray;

    const float kdr_value{ std::stof(kdr) };

    if (kdr_value >= 10.0f) return enum_chat_formatting::dark_red;
    if (kdr_value >= 5.0f) return enum_chat_formatting::red;
    if (kdr_value >= 3.0f) return enum_chat_formatting::gold;
    if (kdr_value >= 2.0f) return enum_chat_formatting::dark_green;
    if (kdr_value >= 1.0f) return enum_chat_formatting::green;
    return enum_chat_formatting::gray;
}

auto npno::blitz_survival_games::assign_team_colors() 
    -> void
{
    const std::vector<std::string> base_colors =
    {
        enum_chat_formatting::dark_aqua,
        enum_chat_formatting::black,
        enum_chat_formatting::dark_blue,
        enum_chat_formatting::dark_green,
        enum_chat_formatting::dark_red,
        enum_chat_formatting::dark_purple,
        enum_chat_formatting::gold,
        enum_chat_formatting::gray,
        enum_chat_formatting::blue,
        enum_chat_formatting::green,
        enum_chat_formatting::aqua,
        enum_chat_formatting::red,
        enum_chat_formatting::light_purple,
        enum_chat_formatting::yellow,
        enum_chat_formatting::white
    };

    bool forbidden_team_exists{ false };
    for (const auto& [team, _] : this->sorted_teams)
    {
        if (team.hypixel_team == "§fshuffleTeam" or team.hypixel_team.starts_with("§k"))
        {
            forbidden_team_exists = true;
        }
    }

    if (forbidden_team_exists)
    {
        return;
    }

    for (const auto& [team, _] : this->sorted_teams)
    {
        const std::string& team_name{ team.hypixel_team };
        if (this->team_colors.find(team_name) == this->team_colors.end())
        {
            std::string color{ base_colors[this->next_color_index % base_colors.size()] };
            if (next_color_index >= base_colors.size())
            {
                color = enum_chat_formatting::bold + color;
            }

            this->team_colors[team_name] = color;
            ++this->next_color_index;
        }
    }
}