#pragma once

#include "../../Network/Network.h"
#include "../../Config/Config.h"
#include "../../HypixelRank/HypixelRank.h"
#include "../../HypixelGamemode/HypixelGamemode.h"

#include <string>
#include <vector>
#include <map>

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