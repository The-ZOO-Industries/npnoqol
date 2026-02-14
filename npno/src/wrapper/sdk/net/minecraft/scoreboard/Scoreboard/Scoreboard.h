#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/net/minecraft/scoreboard/Score/Score.h"
#include "../../src/wrapper/sdk/net/minecraft/scoreboard/ScoreObjective/ScoreObjective.h"
#include "../../src/wrapper/sdk/net/minecraft/scoreboard/ScorePlayerTeam/ScorePlayerTeam.h"
#include "../../src/wrapper/sdk/java/util/List/List.h"

class Scoreboard final : public JavaClass
{
public:
    explicit Scoreboard(maps::Scoreboard instance);

    virtual ~Scoreboard() override;

    enum class DisplaySlot : I8
    {
        LIST,
        SIDEBAR,
        BELOW_NAME
    };

    [[nodiscard]] bool AddPlayerToTeam(const std::string& playerName, const std::string& teamName) const;

    [[nodiscard]] std::unique_ptr<ScorePlayerTeam> GetTeam(const std::string& teamName) const;
    [[nodiscard]] std::unique_ptr<ScorePlayerTeam> GetPlayersTeam(const std::string& playerName) const;
    [[nodiscard]] std::unique_ptr<ScorePlayerTeam> CreateTeam(const std::string& teamName) const;

    [[nodiscard]] std::unique_ptr<ScoreObjective> GetObjectiveInDisplaySlot(const DisplaySlot slot) const;

    [[nodiscard]] std::vector<std::unique_ptr<ScorePlayerTeam>> GetTeams() const;

    [[nodiscard]] std::vector<std::unique_ptr<Score>> GetSortedScores(const std::unique_ptr<ScoreObjective>& objective) const;

    void RemoveTeam(const std::unique_ptr<ScorePlayerTeam>& team) const;
    void RemovePlayerFromTeam(const std::string& playerName, const std::unique_ptr<ScorePlayerTeam>& team) const;
    void SetObjectiveInDisplaySlot(const DisplaySlot slot, const std::unique_ptr<ScoreObjective>& objective) const;
};