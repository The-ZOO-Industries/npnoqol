#pragma once

#include <string>

namespace enum_chat_formatting
{
    inline const std::string black{ "§0" };
    inline const std::string dark_blue{ "§1" };
    inline const std::string dark_green{ "§2" };
    inline const std::string dark_aqua{ "§3" };
    inline const std::string dark_red{ "§4" };
    inline const std::string dark_purple{ "§5" };
    inline const std::string gold{ "§6" };
    inline const std::string gray{ "§7" };
    inline const std::string dark_gray{ "§8" };
    inline const std::string blue{ "§9" };
    inline const std::string green{ "§a" };
    inline const std::string aqua{ "§b" };
    inline const std::string red{ "§c" };
    inline const std::string light_purple{ "§d" };
    inline const std::string yellow{ "§e" };
    inline const std::string white{ "§f" };

    inline const std::string obfuscated{ "§k" };
    inline const std::string bold{ "§l" };
    inline const std::string strikethrough{ "§m" };
    inline const std::string underline{ "§n" };
    inline const std::string italic{ "§o" };
    inline const std::string reset{ "§r" };

    inline const std::map<std::string, std::string> color_by_name =
    {
        {"BLACK", black},
        {"DARK_BLUE", dark_blue},
        {"DARK_GREEN", dark_green},
        {"DARK_AQUA", dark_aqua},
        {"DARK_RED", dark_red},
        {"DARK_PURPLE", dark_purple},
        {"GOLD", gold},
        {"GRAY", gray},
        {"DARK_GRAY", dark_gray},
        {"BLUE", blue},
        {"GREEN", green},
        {"AQUA", aqua},
        {"RED", red},
        {"LIGHT_PURPLE", light_purple},
        {"YELLOW", yellow},
        {"WHITE", white}
    };
}