#include "Config.hpp"

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

auto Config::GetAutoGGLines() -> std::vector<std::string>
{
	std::ifstream file{"autogg.json"};
	if (!file.is_open())
	{
		std::ofstream outFile{"autogg.json"};
		nlohmann::json defaultConfig = nlohmann::json::array();
		outFile << defaultConfig.dump(4);
		return {};
	}

	try
	{
		const nlohmann::json json{nlohmann::json::parse(file)};
		return json.get<std::vector<std::string>>();
	}
	catch (...)
	{
		return {};
	}
}

auto Config::GetBlackListedLines() -> std::vector<std::string>
{
	std::ifstream file{"blacklistes_lines.json"};
	if (!file.is_open())
	{
		std::ofstream outFile{"blacklistes_lines.json"};
		nlohmann::json defaultConfig = nlohmann::json::array();
		outFile << defaultConfig.dump(4);
		return {};
	}

	try
	{
		const nlohmann::json json{nlohmann::json::parse(file)};
		return json.get<std::vector<std::string>>();
	}
	catch (...)
	{
		return {};
	}
}

auto Config::GetNickSkins() -> std::vector<std::string>
{
	std::ifstream file{"nick_skins.json"};
	if (!file.is_open())
	{
		std::ofstream outFile{"nick_skins.json"};
		nlohmann::json defaultConfig = nlohmann::json::array();
		outFile << defaultConfig.dump(4);
		return {};
	}

	try
	{
		const nlohmann::json json{nlohmann::json::parse(file)};
		return json.get<std::vector<std::string>>();
	}
	catch (...)
	{
		return {};
	}
}