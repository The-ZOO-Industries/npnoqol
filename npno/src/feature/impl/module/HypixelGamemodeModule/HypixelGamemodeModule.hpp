#pragma once

#include "../Module/Module.hpp"

class HypixelGamemodeModule : public Module
{
public:
    explicit HypixelGamemodeModule(const bool enable = true, const HypixelGamemode::Gamemode gamemode = HypixelGamemode::Gamemode::ALL);

    virtual ~HypixelGamemodeModule();

    auto SanityCheck() const -> bool override;

    auto ClearCache() -> void override;

protected:
    struct Player
    {
        std::string prefi{ "" };
        std::string rank{ "" };
        std::string suffix{ "" };

        bool isNick{ false };
        bool error{ false };

        bool isLoading{ false };

        I32 retryCount{ 0 };

        std::chrono::steady_clock::time_point lastRequestTime;
        std::chrono::steady_clock::time_point cacheTime;
    };

    struct Team
    {
        std::string playerName{ "" };
        std::string hypixelTeam{ "" };
        std::string npnoTeam{ "" };
    };

    auto UpdateTabList() -> void;
    auto UpdateNameTags() -> void;

    auto IsBot(const std::unique_ptr<EntityPlayer>& player) -> bool;

    virtual auto GetPlayerData(const std::string& playerName) -> Player;

    virtual auto LoadPlayersData(const std::vector<std::string>& playerNames) -> void {};

    virtual auto LoadMissingPlayers() -> void;

    virtual auto FormatTabName(const std::unique_ptr<EntityPlayer>& player) -> std::string { return ""; };
    virtual auto FormatNametag(const std::unique_ptr<EntityPlayer>& player) -> std::pair<std::string, std::string> { return { "", "" }; };

    virtual auto GetHpColor(const float hp) const -> std::string;

    virtual auto HandleMode() -> void {};

    virtual auto GetTeamFromTeamManager(const std::string& playerName) const -> Team final;

    virtual auto GetTeamEntry(const std::string& playerName) -> Team* final;

    virtual	auto SentByServer(const std::string& line) const -> bool final;

    virtual auto OrginizeTeams() -> void final;

    mutable std::unordered_map<std::string, Player> playerCache;

    mutable std::set<std::string> loadingPlayers;

    mutable std::unordered_map<std::string, std::vector<Team>> sortedTeams;
    mutable std::vector<Team> teamManager;

    HypixelGamemode::Gamemode gamemode;
};