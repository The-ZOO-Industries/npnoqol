#pragma once

#include "../../Network/Network.hpp"
#include "../../Config/Config.hpp"
#include "../../HypixelRank/HypixelRank.hpp"
#include "../../HypixelGamemode/HypixelGamemode.hpp"

#include <string>
#include <vector>
#include <map>
#include <print>

#include <nlohmann/json.hpp>

class HypixelAPI final
{
public:
	static auto CheckKey() -> bool;

	static auto IsNicked(const nlohmann::json& json) -> bool;

	static auto GetPlayerStats(const std::string& playerName) -> nlohmann::json;

	static auto SetAPIKey(const std::string& key) -> void;

private:
	inline static std::string apiKey{ Config::GetHypixelAPIKey()};
};