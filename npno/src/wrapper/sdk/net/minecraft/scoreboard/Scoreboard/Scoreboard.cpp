#include "Scoreboard.h"

Scoreboard::Scoreboard(maps::Scoreboard instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

Scoreboard::~Scoreboard() = default;

bool Scoreboard::AddPlayerToTeam(const std::string& playerName, const std::string& teamName) const
{
    jstring jPlayerName = JavaUtil::StringToJString(playerName);
    jstring jTeamName = JavaUtil::StringToJString(teamName);
    maps::String playerStr{ jPlayerName };
    maps::String teamStr{ jTeamName };
    return maps::Scoreboard(this->instance.object_instance).addPlayerToTeam.call(playerStr, teamStr);
}

std::unique_ptr<ScorePlayerTeam> Scoreboard::GetTeam(const std::string& teamName) const
{
    jstring jTeamName = JavaUtil::StringToJString(teamName);
    maps::String teamStr{ jTeamName };
    maps::ScorePlayerTeam team = maps::Scoreboard(this->instance.object_instance).getTeam.call(teamStr);
    maps::ScorePlayerTeam globalTeam{ team.object_instance, true };
    return std::make_unique<ScorePlayerTeam>(globalTeam);
}

std::unique_ptr<ScorePlayerTeam> Scoreboard::GetPlayersTeam(const std::string& playerName) const
{
    jstring jPlayerName = JavaUtil::StringToJString(playerName);
    maps::String playerStr{ jPlayerName };
    maps::ScorePlayerTeam team = maps::Scoreboard(this->instance.object_instance).getPlayersTeam.call(playerStr);
    maps::ScorePlayerTeam globalTeam{ team.object_instance, true };
    return std::make_unique<ScorePlayerTeam>(globalTeam);
}

std::unique_ptr<ScorePlayerTeam> Scoreboard::CreateTeam(const std::string& teamName) const
{
    jstring jTeamName = JavaUtil::StringToJString(teamName);
    maps::String teamStr{ jTeamName };
    maps::ScorePlayerTeam team = maps::Scoreboard(this->instance.object_instance).createTeam.call(teamStr);
    maps::ScorePlayerTeam globalTeam{ team.object_instance, true };
    return std::make_unique<ScorePlayerTeam>(globalTeam);
}

std::unique_ptr<ScoreObjective> Scoreboard::GetObjectiveInDisplaySlot(const DisplaySlot slot) const
{
    maps::ScoreObjective objective = maps::Scoreboard(this->instance.object_instance).getObjectiveInDisplaySlot.call(static_cast<jint>(slot));
    maps::ScoreObjective globalObjective{ objective.object_instance, true };
    return std::make_unique<ScoreObjective>(globalObjective);
}

std::vector<std::unique_ptr<ScorePlayerTeam>> Scoreboard::GetTeams() const
{
    std::vector<std::unique_ptr<ScorePlayerTeam>> teamList{};

    maps::Collection collection = maps::Scoreboard(this->instance.object_instance).getTeams.call();
    jni::array<maps::Object> array = collection.toArray.call();
    std::vector<maps::Object> vec = array.to_vector();

    for (maps::Object& obj : vec)
    {
        maps::ScorePlayerTeam team{ obj.object_instance, true };
        teamList.emplace_back(std::make_unique<ScorePlayerTeam>(team));
    }

    return teamList;
}

std::vector<std::unique_ptr<Score>> Scoreboard::GetSortedScores(const std::unique_ptr<ScoreObjective>& objective) const
{
    std::vector<std::unique_ptr<Score>> scoreList{};

    maps::ScoreObjective objParam{ objective->GetInstance().object_instance };
    maps::Collection collection = maps::Scoreboard(this->instance.object_instance).getSortedScores.call(objParam);
    jni::array<maps::Object> array = collection.toArray.call();
    std::vector<maps::Object> vec = array.to_vector();

    for (maps::Object& obj : vec)
    {
        maps::Score score{ obj.object_instance, true };
        scoreList.push_back(std::make_unique<Score>(score));
    }

    return scoreList;
}

void Scoreboard::RemoveTeam(const std::unique_ptr<ScorePlayerTeam>& team) const
{
    maps::ScorePlayerTeam teamParam{ team->GetInstance().object_instance };
    maps::Scoreboard(this->instance.object_instance).removeTeam.call(teamParam);
}

void Scoreboard::RemovePlayerFromTeam(const std::string& playerName, const std::unique_ptr<ScorePlayerTeam>& team) const
{
    jstring jPlayerName = JavaUtil::StringToJString(playerName);
    maps::String playerStr{ jPlayerName };
    maps::ScorePlayerTeam teamParam{ team->GetInstance().object_instance };
    maps::Scoreboard(this->instance.object_instance).removePlayerFromTeam.call(playerStr, teamParam);
}

void Scoreboard::SetObjectiveInDisplaySlot(const DisplaySlot slot, const std::unique_ptr<ScoreObjective>& objective) const
{
    maps::ScoreObjective objParam{ objective ? objective->GetInstance().object_instance : nullptr };
    maps::Scoreboard(this->instance.object_instance).setObjectiveInDisplaySlot.call(static_cast<jint>(slot), objParam);
}