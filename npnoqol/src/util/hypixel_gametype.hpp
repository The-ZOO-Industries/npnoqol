#pragma once

#include <string>
#include <unordered_map>

namespace hypixel_gametype
{
    enum class gametype : std::int32_t
    {
        UNKNOWN,

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

    inline hypixel_gametype::gametype current_gametype{ hypixel_gametype::gametype::LOBBY };

    inline const std::unordered_map<std::string, hypixel_gametype::gametype> string_to_gametype =
    {
        {"UNKNOWN", hypixel_gametype::gametype::UNKNOWN},
        {"LOBBY", hypixel_gametype::gametype::LOBBY},
        {"QUAKECRAFT", hypixel_gametype::gametype::QUAKECRAFT},
        {"WALLS", hypixel_gametype::gametype::WALLS},
        {"PAINTBALL", hypixel_gametype::gametype::PAINTBALL},
        {"SURVIVAL_GAMES", hypixel_gametype::gametype::BLITZSURVIVALGAMES},
        {"TNTGAMES", hypixel_gametype::gametype::TNTGAMES},
        {"VAMPIREZ", hypixel_gametype::gametype::VAMPIREZ},
        {"WALLS3", hypixel_gametype::gametype::WALLS3},
        {"ARCADE", hypixel_gametype::gametype::ARCADE},
        {"ARENA", hypixel_gametype::gametype::ARENA},
        {"UHC", hypixel_gametype::gametype::UHC},
        {"MCGO", hypixel_gametype::gametype::MCGO},
        {"BATTLEGROUND", hypixel_gametype::gametype::BATTLEGROUND},
        {"SUPER_SMASH", hypixel_gametype::gametype::SUPER_SMASH},
        {"GINGERBREAD", hypixel_gametype::gametype::GINGERBREAD},
        {"HOUSING", hypixel_gametype::gametype::HOUSING},
        {"SKYWARS", hypixel_gametype::gametype::SKYWARS},
        {"TRUE_COMBAT", hypixel_gametype::gametype::TRUE_COMBAT},
        {"SPEED_UHC", hypixel_gametype::gametype::SPEED_UHC},
        {"SKYCLASH", hypixel_gametype::gametype::SKYCLASH},
        {"LEGACY", hypixel_gametype::gametype::LEGACY},
        {"PROTOTYPE", hypixel_gametype::gametype::PROTOTYPE},
        {"BEDWARS", hypixel_gametype::gametype::BEDWARS},
        {"MURDER_MYSTERY", hypixel_gametype::gametype::MURDER_MYSTERY},
        {"BUILD_BATTLE", hypixel_gametype::gametype::BUILD_BATTLE},
        {"DUELS", hypixel_gametype::gametype::DUELS},
        {"SKYBLOCK", hypixel_gametype::gametype::SKYBLOCK},
        {"PIT", hypixel_gametype::gametype::PIT},
        {"REPLAY", hypixel_gametype::gametype::REPLAY},
        {"SMP", hypixel_gametype::gametype::SMP},
        {"WOOL_GAMES", hypixel_gametype::gametype::WOOL_GAMES}
    };
}