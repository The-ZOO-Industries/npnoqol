#include "GamemodeManager.hpp"

GamemodeManager::GamemodeManager()
    : Module{ true }
{
    
}

GamemodeManager::~GamemodeManager() = default;

auto GamemodeManager::Update() -> void
{
    for (const std::string& line : ChatUtil::GetNewLines())
    {
        const std::string jsonPart{ ExtractJson(line) };
        if (nlohmann::json::accept(jsonPart))
        {
            const nlohmann::json json{ nlohmann::json::parse(jsonPart) };

            if (json.contains("gametype"))
            {
                currentGamemode = json.at("gametype");
            }

            if (json.contains("mode"))
            {
                currentMode = json.at("mode");
            }
            else
            {
                currentMode = "unknown";
            }
        }
    }
}

auto GamemodeManager::GetCurrentGamemode() -> std::string
{
    return currentGamemode;
}

auto GamemodeManager::GetCurrentMode() -> std::string
{
    return currentMode;
}

auto GamemodeManager::ExtractJson(const std::string& line) -> std::string
{
    const Size pos{ line.find('{') };
    if (pos != std::string::npos) 
    {
        return line.substr(pos);
    }
    return "";
}