#pragma once

#include "../command.hpp"

namespace npno
{
	class requeue final : public npno::command
	{
	public:
		requeue();

		~requeue();

		virtual auto on_command(const std::vector<std::string>& args) const
			-> void override;

	private:
		struct gametype_mode_hash
		{
			auto operator()(const std::pair<hypixel_gametype::gametype, std::string>& value) const 
				-> std::size_t
			{
				const std::size_t h1{ std::hash<std::int32_t>{}(static_cast<std::int32_t>(value.first)) };
				const std::size_t h2{ std::hash<std::string>{}(value.second) };
				return h1 ^ (h2 << 1);
			}
		};

		inline static const std::unordered_map<std::pair<hypixel_gametype::gametype, std::string>, std::string, gametype_mode_hash> command_map =
		{
			{ { hypixel_gametype::gametype::BLITZSURVIVALGAMES, "solo_normal" }, "/play blitz_solo_normal" },
			{ { hypixel_gametype::gametype::BLITZSURVIVALGAMES, "teams_normal" }, "/play blitz_teams_normal" },

			{ { hypixel_gametype::gametype::SKYWARS, "mini_normal" }, "/play mini_normal" },
			{ { hypixel_gametype::gametype::SKYWARS, "solo_normal" }, "/play solo_normal" },
			{ { hypixel_gametype::gametype::SKYWARS, "teams_normal" }, "/play teams_normal" },
			{ { hypixel_gametype::gametype::SKYWARS, "solo_insane" }, "/play solo_insane" },
			{ { hypixel_gametype::gametype::SKYWARS, "solo_insane_lucky" }, "/play solo_insane_lucky" },
			{ { hypixel_gametype::gametype::SKYWARS, "teams_insane_lucky" }, "/play teams_insane_lucky" },

			{ { hypixel_gametype::gametype::BEDWARS, "BEDWARS_EIGHT_ONE" }, "/play bedwars_eight_one" },
			{ { hypixel_gametype::gametype::BEDWARS, "BEDWARS_EIGHT_TWO" }, "/play bedwars_eight_two" },
			{ { hypixel_gametype::gametype::BEDWARS, "BEDWARS_FOUR_THREE" }, "/play bedwars_four_three" },
			{ { hypixel_gametype::gametype::BEDWARS, "BEDWARS_FOUR_FOUR" }, "/play bedwars_four_four" },
			{ { hypixel_gametype::gametype::BEDWARS, "BEDWARS_TWO_FOUR" }, "/play bedwars_two_four" },
			{ { hypixel_gametype::gametype::BEDWARS, "BEDWARS_EIGHT_TWO_VOIDLESS" }, "/play bedwars_eight_two_voidless" },
			{ { hypixel_gametype::gametype::BEDWARS, "BEDWARS_FOUR_FOUR_VOIDLESS" }, "/play bedwars_four_four_voidless" },

			{ { hypixel_gametype::gametype::BATTLEGROUND, "ctf_mini" }, "/play warlords_ctf_mini" },
			{ { hypixel_gametype::gametype::BATTLEGROUND, "domination" }, "/play warlords_domination" },
			{ { hypixel_gametype::gametype::BATTLEGROUND, "team_deathmatch" }, "/play warlords_team_deathmatch" },

			{ { hypixel_gametype::gametype::ARENA, "1v1" }, "/play arena_1v1" },
			{ { hypixel_gametype::gametype::ARENA, "2v2" }, "/play arena_2v2" },
			{ { hypixel_gametype::gametype::ARENA, "4v4" }, "/play arena_4v4" },

			{ { hypixel_gametype::gametype::VAMPIREZ, "normal" }, "/play vampirez" },

			{ { hypixel_gametype::gametype::GINGERBREAD, "normal" }, "/play tkr" },

			{ { hypixel_gametype::gametype::PAINTBALL, "normal" }, "/play paintball" },

			{ { hypixel_gametype::gametype::WALLS, "normal" }, "/play walls" },

			{ { hypixel_gametype::gametype::QUAKECRAFT, "solo" }, "/play quake_solo" },
			{ { hypixel_gametype::gametype::QUAKECRAFT, "teams" }, "/play quake_teams" },

			{ { hypixel_gametype::gametype::SUPER_SMASH, "solo_normal" }, "/play super_smash_solo_normal" },
			{ { hypixel_gametype::gametype::SUPER_SMASH, "teams_normal" }, "/play super_smash_teams_normal" },
			{ { hypixel_gametype::gametype::SUPER_SMASH, "1v1_normal" }, "/play super_smash_1v1_normal" },
			{ { hypixel_gametype::gametype::SUPER_SMASH, "2v2_normal" }, "/play super_smash_2v2_normal" },

			{ { hypixel_gametype::gametype::MCGO, "normal" }, "/play mcgo_normal" },
			{ { hypixel_gametype::gametype::MCGO, "gungame" }, "/play mcgo_deathmatch" },
			{ { hypixel_gametype::gametype::MCGO, "deathmatch" }, "/play mcgo_gungame" },

			{ { hypixel_gametype::gametype::SPEED_UHC, "solo_normal" }, "/play speed_solo_normal" },
			{ { hypixel_gametype::gametype::SPEED_UHC, "team_normal" }, "/play speed_team_normal" },

			{ { hypixel_gametype::gametype::DUELS, "DUELS_BOW_DUEL" }, "/play duels_bow_duel" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_MW_DUEL" }, "/play duels_mw_duel" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_PARKOUR_EIGHT" }, "/play duels_parkour_eight" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_QUAKE_DUEL" }, "/play duels_quake_duel" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_BOWSPLEEF_DUEL" }, "/play duels_bowspleef_duel" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_SPLEEF_DUEL" }, "/play duels_spleef_duel" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_OP_DUEL" }, "/play duels_op_duel" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_OP_DOUBLES" }, "/play duels_op_doubles" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_BLITZ_DUEL" }, "/play duels_blitz_duel" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_COMBO_DUEL" }, "/play duels_combo_duel" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_BOXING_DUEL" }, "/play duels_boxing_duel" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_POTION_DUEL" }, "/play duels_potion_duel" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_SW_DUEL" }, "/play duels_sw_duel" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_SW_DOUBLES" }, "/play duels_sw_doubles" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_BRIDGE_DUEL" }, "/play duels_bridge_duel" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_BRIDGE_DOUBLES" }, "/play duels_bridge_doubles" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_BRIDGE_THREES" }, "/play duels_bridge_threes" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_BRIDGE_FOUR" }, "/play duels_bridge_four" },
			{ { hypixel_gametype::gametype::DUELS, "BEDWARS_TWO_ONE_DUELS" }, "/play bedwars_two_one_duels" },
			{ { hypixel_gametype::gametype::DUELS, "BEDWARS_TWO_ONE_DUELS_RUSH" }, "/play bedwars_two_one_duels_rush" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_CLASSIC_DUEL" }, "/play duels_classic_duel" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_CLASSIC_DOUBLES" }, "/play duels_classic_doubles" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_UHC_DUEL" }, "/play duels_uhc_duel" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_UHC_DOUBLES" }, "/play duels_uhc_doubles" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_UHC_FOUR" }, "/play duels_uhc_four" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_UHC_MEETUP" }, "/play duels_uhc_meetup" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_SUMO_DUEL" }, "/play duels_sumo_duel" },
			{ { hypixel_gametype::gametype::DUELS, "DUELS_DUEL_ARENA" }, "/play duels_duel_arena" },

			{ { hypixel_gametype::gametype::BUILD_BATTLE, "BUILD_BATTLE_SPEED_BUILDERS" }, "/play build_battle_speed_builders" },
			{ { hypixel_gametype::gametype::BUILD_BATTLE, "BUILD_BATTLE_GUESS_THE_BUILD" }, "/play build_battle_guess_the_build" },

			{ { hypixel_gametype::gametype::MURDER_MYSTERY, "MURDER_ASSASSINS" }, "/play murder_assassins" },
			{ { hypixel_gametype::gametype::MURDER_MYSTERY, "MURDER_CLASSIC" }, "/play murder_classic" },
			{ { hypixel_gametype::gametype::MURDER_MYSTERY, "MURDER_DOUBLE_UP" }, "/play murder_double_up" },
			{ { hypixel_gametype::gametype::MURDER_MYSTERY, "MURDER_INFECTION" }, "/play murder_infection" }
		};
	};
}