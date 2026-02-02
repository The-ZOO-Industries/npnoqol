#pragma once

#include <string>
#include <map>

namespace MinecraftCode
{
    inline const std::string BLACK{ "§0" };
    inline const std::string DARK_BLUE{ "§1" };
    inline const std::string DARK_GREEN{ "§2" };
    inline const std::string DARK_AQUA{ "§3" };
    inline const std::string DARK_RED{ "§4" };
    inline const std::string DARK_PURPLE{ "§5" };
    inline const std::string GOLD{ "§6" };
    inline const std::string GRAY{ "§7" };
    inline const std::string DARK_GRAY{ "§8" };
    inline const std::string BLUE{ "§9" };
    inline const std::string GREEN{ "§a" };
    inline const std::string AQUA{ "§b" };
    inline const std::string RED{ "§c" };
    inline const std::string LIGHT_PURPLE{ "§d" };
    inline const std::string YELLOW{ "§e" };
    inline const std::string WHITE{ "§f" };

    inline const std::string OBFUSCATED{ "§k" };
    inline const std::string BOLD{ "§l" };
    inline const std::string STRIKETHROUGH{ "§m" };
    inline const std::string UNDERLINE{ "§n" };
    inline const std::string ITALIC{ "§o" };
    inline const std::string RESET{ "§r" };

    inline const std::map<std::string, std::string> ColorByName
    {
        {"BLACK", BLACK},
        {"DARK_BLUE", DARK_BLUE},
        {"DARK_GREEN", DARK_GREEN},
        {"DARK_AQUA", DARK_AQUA},
        {"DARK_RED", DARK_RED},
        {"DARK_PURPLE", DARK_PURPLE},
        {"GOLD", GOLD},
        {"GRAY", GRAY},
        {"DARK_GRAY", DARK_GRAY},
        {"BLUE", BLUE},
        {"GREEN", GREEN},
        {"AQUA", AQUA},
        {"RED", RED},
        {"LIGHT_PURPLE", LIGHT_PURPLE},
        {"YELLOW", YELLOW},
        {"WHITE", WHITE}
    };
}