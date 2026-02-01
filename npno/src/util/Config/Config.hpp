#pragma once

#include <string>
#include <print>
#include <fstream>

#include <nlohmann/json.hpp>

class Config final
{
public:
	static auto GetHypixelAPIKey() -> std::string;

	static auto SetHypixelAPIKey(const std::string& apiKey) -> void;
};