#include "HypixelRank.hpp"

#include "../MinecraftCode/MinecraftCode.hpp"

auto HypixelRank::GetRankPrefix(const nlohmann::json& json) -> std::string
{
    const auto playerIt = json.find("player");
    if (playerIt == json.end() or !playerIt->is_object())
    {
        return {};
    }

    const auto& player = *playerIt;

    auto getColorByName = [](const std::string& name) -> std::string
        {
            const auto it = MinecraftCode::ColorByName.find(name);
            return it != MinecraftCode::ColorByName.end() ? it->second : std::string{};
        };

    std::string plusColor{ MinecraftCode::RED };

    if (player.contains("rankPlusColor") and player["rankPlusColor"].is_string())
    {
        const auto color = getColorByName(player["rankPlusColor"].get<std::string>());
        if (!color.empty())
        {
            plusColor = color;
        }
    }

    std::string monthlyRank{ player.value("monthlyPackageRank", "") };
    std::string packageRank{ player.value("newPackageRank", "") };

    if (monthlyRank == "SUPERSTAR")
    {
        std::string rankColor{ MinecraftCode::GOLD };

        if (player.contains("monthlyRankColor") and player["monthlyRankColor"].is_string())
        {
            const auto color = getColorByName(player["monthlyRankColor"].get<std::string>());
            if (!color.empty())
            {
                rankColor = color;
            }
        }

        return rankColor + "[MVP" + plusColor + "++" + rankColor + "]";
    }

    if (packageRank == "MVP_PLUS")
    {
        return MinecraftCode::AQUA + "[MVP" + plusColor + "+" + MinecraftCode::AQUA + "]";
    }

    if (packageRank == "MVP")
    {
        return MinecraftCode::AQUA + "[MVP]";
    }

    if (packageRank == "VIP_PLUS")
    {
        return MinecraftCode::GREEN + "[VIP" + MinecraftCode::GOLD + "+" + MinecraftCode::GREEN + "]";
    }

    if (packageRank == "VIP")
    {
        return MinecraftCode::GREEN + "[VIP]";
    }

    return {};
}