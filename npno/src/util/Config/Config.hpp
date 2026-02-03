#pragma once

#include <string>
#include <print>
#include <vector>
#include <fstream>

#include <nlohmann/json.hpp>

class Config final
{
public:
	static auto GetHypixelAPIKey() -> std::string;
	static auto SetHypixelAPIKey(const std::string& apiKey) -> void;

	static auto GetAutoGGLines() -> std::vector<std::regex>;
	
	static auto GetBlackListedLines() -> std::vector<std::string>;

	static auto GetNickSkins() -> std::vector<std::string>;
};