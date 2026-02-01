#pragma once

#include "../../HypixelModule/HypixelModule.hpp"

class BlitzSurvivalGames final : public HypixelModule
{
public:
    BlitzSurvivalGames();
    ~BlitzSurvivalGames() override;

    auto Update() -> void override;

private:
    enum class Mode : I8
    {
        SOLO,
        TEAMS,
        LOBBY
    };

    auto LoadPlayersData(const std::vector<std::string>& playerNames) -> void override;
    auto HandleMode() -> void override;
    auto UpdateChat() const -> void;

    auto FormatTabName(const std::unique_ptr<EntityPlayer>& player) -> std::string override;
    auto FormatNametag(const std::unique_ptr<EntityPlayer>& player) -> std::pair<std::string, std::string> override;

    auto GetWinsColor(const std::string& wins) const -> std::string;
    auto GetKDRColor(const std::string& kdr) const -> std::string;

    auto AssignTeamColors() -> void;

    std::unordered_map<std::string, std::string> teamColors;
    U32 nextColorIndex{ 0 };

    Mode mode;
};