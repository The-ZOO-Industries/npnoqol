#pragma once

#include <string>

#include <nlohmann/json.hpp>

class HypixelRank final
{
public:
    static auto GetRankPrefix(const nlohmann::json& json) -> std::string;
};