#pragma once

#include "../Module/Module.hpp"

class HypixelModule : public Module
{
public:
    explicit HypixelModule(const bool enable, const Hypixel::Gamemode gamemode = Hypixel::Gamemode::ALL);

    virtual ~HypixelModule();

    auto ClearCache() -> void override;

    auto SanityCheck() const -> bool override;

    auto GetGamemode() const -> Hypixel::Gamemode;

protected:
    struct Player
    {
        std::string prefix;
        std::string rank;
        std::string suffix;

        bool isNick{ false };
        bool error{ false };
        bool isLoading{ false };

        I32 retryCount{ 0 };

        std::chrono::steady_clock::time_point lastRequestTime;
        std::chrono::steady_clock::time_point cacheTime;
    };

    struct Team
    {
        std::string playerName;
        std::string hypixelTeam;
        std::string npnoTeam;
    };

    auto UpdateTabList() -> void;
    auto UpdateNameTags() -> void;

    virtual auto GetPlayerData(const std::string& playerName) -> Player;

    virtual auto LoadPlayersData(const std::vector<std::string>& playerNames) -> void = 0;

    virtual auto LoadMissingPlayers() -> void;

    virtual auto FormatTabName(const std::unique_ptr<EntityPlayer>& player) -> std::string = 0;
    virtual auto FormatNametag(const std::unique_ptr<EntityPlayer>& player) -> std::pair<std::string, std::string> = 0;

    virtual auto GetHpColor(const float hp) const -> std::string;

    virtual auto HandleMode() -> void = 0;

    virtual auto GetTeamFromTeamManager(const std::string& playerName) const -> Team final;
    virtual auto GetTeamEntry(const std::string& playerName) -> Team* final;
    virtual auto OrginizeTeams() -> void final;

    std::unordered_map<std::string, Player> playerCache;
    std::set<std::string> loadingPlayers;
    std::unordered_map<std::string, std::vector<Team>> sortedTeams;
    std::vector<Team> teamManager;

    Hypixel::Gamemode gamemode;
};