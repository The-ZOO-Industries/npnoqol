#pragma once

#include "network.hpp"
#include "config.hpp"
#include "enum_chat_formatting.hpp"

#include <string>
#include <vector>
#include <thread>
#include <mutex>

namespace hypixel_api
{
    static auto check_apikey(const std::string& api_key)
        -> bool
    {
        try
        {
            const std::string result{ network::get(std::format("/v2/key?key={}", api_key), network::url::HYPIXEL) };
            if (nlohmann::json::accept(result))
            {
                const nlohmann::json json_response{ nlohmann::json::parse(result, nullptr, false) };
                if (json_response["cause"] == "Invalid API key")
                {
                    return false;
                }

                config::set<std::string>("api.hypixel", api_key);

                return true;
            }

            return false;
        }
        catch (...)
        {
            return false;
        }
    }

    static auto get_player_stats(const std::string& player)
        -> nlohmann::json
    {
        const std::string result{ network::get(
            std::format("/player?key={}&name={}", config::get<std::string>("api.hypixel"), player),
            network::url::HYPIXEL
        ) };

        if (nlohmann::json::accept(result))
        {
            const nlohmann::json json_response{ nlohmann::json::parse(result, nullptr, false) };

            return json_response;
        }

        return nlohmann::json{};
    }

    static auto get_players_stats(const std::vector<std::string>& players)
        -> std::vector<nlohmann::json>
    {
        std::vector<nlohmann::json> results{};
        results.resize(players.size());

        std::vector<std::thread> threads{};
        std::mutex mutex{};

        for (std::size_t i{}; i < players.size(); ++i)
        {
            threads.emplace_back([&, i]()
                {
                    const nlohmann::json stats{ get_player_stats(players[i]) };

                    std::lock_guard<std::mutex> lock{ mutex };
                    results[i] = stats;
                });
        }

        for (auto& thread : threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }

        return results;
    }

    static auto is_nicked(const nlohmann::json& response)
        -> bool
    {
        try
        {
            if (response.contains("player") and response["player"].is_null())
            {
                return true;
            }
        }
        catch (...)
        {
            return false;
        }

        return false;
    }

    static auto get_rank_prefix(const nlohmann::json& response)
        -> std::string
    {
        const auto player_it = response.find("player");
        if (player_it == response.end() or not player_it->is_object())
        {
            return std::string{};
        }

        const auto& player{ *player_it };

        auto get_color_by_name = [](const std::string& name)
            -> std::string
            {
                const auto it = enum_chat_formatting::color_by_name.find(name);
                return it != enum_chat_formatting::color_by_name.end() ? it->second : std::string{};
            };

        std::string plusColor{ enum_chat_formatting::red };

        if (player.contains("rankPlusColor") and player["rankPlusColor"].is_string())
        {
            const auto color = get_color_by_name(player["rankPlusColor"].get<std::string>());
            if (!color.empty())
            {
                plusColor = color;
            }
        }

        std::string monthlyRank{ player.value("monthlyPackageRank", "") };
        std::string packageRank{ player.value("newPackageRank", "") };

        if (monthlyRank == "SUPERSTAR")
        {
            std::string rankColor{ enum_chat_formatting::gold };

            if (player.contains("monthlyRankColor") and player["monthlyRankColor"].is_string())
            {
                const auto color = get_color_by_name(player["monthlyRankColor"].get<std::string>());
                if (!color.empty())
                {
                    rankColor = color;
                }
            }

            return rankColor + "[MVP" + plusColor + "++" + rankColor + "]";
        }

        if (packageRank == "MVP_PLUS")
        {
            return enum_chat_formatting::aqua + "[MVP" + plusColor + "+" + enum_chat_formatting::aqua + "]";
        }

        if (packageRank == "MVP")
        {
            return enum_chat_formatting::aqua + "[MVP]";
        }

        if (packageRank == "VIP_PLUS")
        {
            return enum_chat_formatting::green + "[VIP" + enum_chat_formatting::gold + "+" + enum_chat_formatting::green + "]";
        }

        if (packageRank == "VIP")
        {
            return enum_chat_formatting::green + "[VIP]";
        }

        return std::string{};
    }
}