#pragma once

#include <string>
#include <unordered_map>

namespace Hypixel
{
    enum class Gamemode : I8
    {
        LOBBY,
        QUAKECRAFT,
        WALLS,
        PAINTBALL,
        BLITZSURVIVALGAMES,
        TNTGAMES,
        VAMPIREZ,
        WALLS3,
        ARCADE,
        ARENA,
        UHC,
        MCGO,
        BATTLEGROUND,
        SUPER_SMASH,
        GINGERBREAD,
        HOUSING,
        SKYWARS,
        TRUE_COMBAT,
        SPEED_UHC,
        SKYCLASH,
        LEGACY,
        PROTOTYPE,
        BEDWARS,
        MURDER_MYSTERY,
        BUILD_BATTLE,
        DUELS,
        SKYBLOCK,
        PIT,
        REPLAY,
        SMP,
        WOOL_GAMES
    };

    inline const std::unordered_map<Gamemode, std::string> GamemodeToString
    {
        {Gamemode::LOBBY, "LOBBY"},
        {Gamemode::QUAKECRAFT, "QUAKECRAFT"},
        {Gamemode::WALLS, "WALLS"},
        {Gamemode::PAINTBALL, "PAINTBALL"},
        {Gamemode::BLITZSURVIVALGAMES, "SURVIVAL_GAMES"}, 
        {Gamemode::TNTGAMES, "TNTGAMES"},
        {Gamemode::VAMPIREZ, "VAMPIREZ"},
        {Gamemode::WALLS3, "WALLS3"},
        {Gamemode::ARCADE, "ARCADE"},
        {Gamemode::ARENA, "ARENA"},
        {Gamemode::UHC, "UHC"},
        {Gamemode::MCGO, "MCGO"},
        {Gamemode::BATTLEGROUND, "BATTLEGROUND"},
        {Gamemode::SUPER_SMASH, "SUPER_SMASH"},
        {Gamemode::GINGERBREAD, "GINGERBREAD"},
        {Gamemode::HOUSING, "HOUSING"},
        {Gamemode::SKYWARS, "SKYWARS"},
        {Gamemode::TRUE_COMBAT, "TRUE_COMBAT"},
        {Gamemode::SPEED_UHC, "SPEED_UHC"},
        {Gamemode::SKYCLASH, "SKYCLASH"},
        {Gamemode::LEGACY, "LEGACY"},
        {Gamemode::PROTOTYPE, "PROTOTYPE"},
        {Gamemode::BEDWARS, "BEDWARS"},
        {Gamemode::MURDER_MYSTERY, "MURDER_MYSTERY"},
        {Gamemode::BUILD_BATTLE, "BUILD_BATTLE"},
        {Gamemode::DUELS, "DUELS"},
        {Gamemode::SKYBLOCK, "SKYBLOCK"},
        {Gamemode::PIT, "PIT"},
        {Gamemode::REPLAY, "REPLAY"},
        {Gamemode::SMP, "SMP"},
        {Gamemode::WOOL_GAMES, "WOOL_GAMES"}
    };

    inline auto ToString(const Gamemode gamemode) -> std::string
    {
        const auto it = GamemodeToString.find(gamemode);
        return it != GamemodeToString.end() ? it->second : std::string{};
    }
}