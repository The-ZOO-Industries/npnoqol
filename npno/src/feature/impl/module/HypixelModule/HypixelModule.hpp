#pragma once

#include "../Module/Module.hpp"

class HypixelModule : public Module
{
public:
    explicit HypixelModule(const bool enable, const Hypixel::Gamemode gamemode = Hypixel::Gamemode::LOBBY);

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
        std::vector<std::string> players;
        std::string hypixelTeam;
        std::string npnoTeam;

        auto operator==(const Team& other) const -> bool
        {
            return hypixelTeam == other.hypixelTeam and npnoTeam == other.npnoTeam;
        }

        auto operator<(const Team& other) const -> bool
        {
            if (hypixelTeam != other.hypixelTeam)
            {
                return hypixelTeam < other.hypixelTeam;
            }
            return npnoTeam < other.npnoTeam;
        }
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

    std::map<Team, std::vector<std::string>> sortedTeams;
    std::unordered_map<std::string, Team> teamManager;

    std::unordered_map<std::string, Player> playerCache;
    std::set<std::string> loadingPlayers;

    Hypixel::Gamemode gamemode;

private:
    auto OrginizeTeams() -> void;
    auto FillTeamManagerWithHypixelTeams() -> void;
    auto AssignNpnoTeams() -> void;
    auto ApplyTeamsAndNametags() -> void;
};