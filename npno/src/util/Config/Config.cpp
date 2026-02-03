#include "Config.hpp"

#include "AutoGGConfig.hpp"
#include "BlacklistedLinesConfig.hpp"
#include "NickSkinsConfig.hpp"

auto Config::GetHypixelAPIKey() -> std::string
{
	std::ifstream file{"config.json"};
	if (!file.is_open())
	{
		std::ofstream outFile{"config.json"};
		nlohmann::json defaultConfig{
			{"api", {
				{"hypixel", ""}
			}}
		};
		outFile << defaultConfig.dump(4);
		return {};
	}

	try
	{
		const nlohmann::json json{nlohmann::json::parse(file)};
		return json.at("api").at("hypixel").get<std::string>();
	}
	catch (...)
	{
		return {};
	}
}

auto Config::SetHypixelAPIKey(const std::string& apiKey) -> void
{
	nlohmann::json config{};

	std::ifstream inFile{"config.json"};
	if (inFile.is_open())
	{
		try
		{
			config = nlohmann::json::parse(inFile);
		}
		catch (...)
		{
			config = {
				{"api", {
					{"hypixel", ""}
				}}
			};
		}
	}
	else
	{
		config = {
			{"api", {
				{"hypixel", ""}
			}}
		};
	}

	config["api"]["hypixel"] = apiKey;

	std::ofstream outFile{"config.json"};
	if (!outFile.is_open())
	{
		return;
	}

	outFile << config.dump(4);
}

auto Config::GetAutoGGLines() -> std::vector<std::regex>
{
	try
	{
		const nlohmann::json json{nlohmann::json::parse(AUTO_GG_JSON)};
		return json.get<std::vector<std::regex>>();
	}
	catch (...)
	{
		return {};
	}
}

auto Config::GetBlackListedLines() -> std::vector<std::string>
{
	try
	{
		const nlohmann::json json{nlohmann::json::parse(BLACKLISTED_LINES_JSON)};
		return json.get<std::vector<std::string>>();
	}
	catch (...)
	{
		return {};
	}
}

auto Config::GetNickSkins() -> std::vector<std::string>
{
	try
	{
		const nlohmann::json json{nlohmann::json::parse(NICK_SKINS_JSON)};
		return json.get<std::vector<std::string>>();
	}
	catch (...)
	{
		return {};
	}
}