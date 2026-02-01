#pragma once

#include "../MinecraftCode/MinecraftCode.hpp"

#include <nlohmann/json.hpp>

class HypixelRank final
{
public:
    static auto GetRankPrefix(const nlohmann::json& json) -> std::string;

private:
    inline static const std::map<std::string, std::string> colorMap =
    {
        {"BLACK", MinecraftCode::BLACK},
        {"DARK_BLUE", MinecraftCode::DARK_BLUE},
        {"DARK_GREEN", MinecraftCode::DARK_GREEN},
        {"DARK_AQUA", MinecraftCode::DARK_AQUA},
        {"DARK_RED", MinecraftCode::DARK_RED},
        {"DARK_PURPLE", MinecraftCode::DARK_PURPLE},
        {"GOLD", MinecraftCode::GOLD},
        {"GRAY", MinecraftCode::GRAY},
        {"DARK_GRAY", MinecraftCode::DARK_GRAY},
        {"BLUE", MinecraftCode::BLUE},
        {"GREEN", MinecraftCode::GREEN},
        {"AQUA", MinecraftCode::AQUA},
        {"RED", MinecraftCode::RED},
        {"LIGHT_PURPLE", MinecraftCode::LIGHT_PURPLE},
        {"YELLOW", MinecraftCode::YELLOW},
        {"WHITE", MinecraftCode::WHITE}
    };
};