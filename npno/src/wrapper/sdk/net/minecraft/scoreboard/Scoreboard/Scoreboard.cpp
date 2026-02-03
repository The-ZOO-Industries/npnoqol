#include "Scoreboard.h"

Scoreboard::Scoreboard(const jobject instance)
    : JavaClass(instance)
{

}

Scoreboard::~Scoreboard() = default;

bool Scoreboard::AddPlayerToTeam(const std::string& playerName, const std::string& teamName) const 
{
    jni::frame f;

    return maps::Scoreboard(this->instance).addPlayerToTeam.call(JavaUtil::StringToJString(playerName), JavaUtil::StringToJString(teamName));
}

std::unique_ptr<ScorePlayerTeam> Scoreboard::GetTeam(const std::string& teamName) const 
{
    jni::frame f;

    return std::make_unique<ScorePlayerTeam>(jni::make_global(maps::Scoreboard(this->instance).getTeam.call(JavaUtil::StringToJString(teamName))));
}

std::unique_ptr<ScorePlayerTeam> Scoreboard::GetPlayersTeam(const std::string& playerName) const
{
    jni::frame f;

    return std::make_unique<ScorePlayerTeam>(jni::make_global( maps::Scoreboard(this->instance).getPlayersTeam.call(JavaUtil::StringToJString(playerName))));
}

std::unique_ptr<ScorePlayerTeam> Scoreboard::CreateTeam(const std::string& teamName) const 
{
    jni::frame f;

    return std::make_unique<ScorePlayerTeam>(jni::make_global(maps::Scoreboard(this->instance).createTeam.call(JavaUtil::StringToJString(teamName))));
}

std::unique_ptr<ScoreObjective> Scoreboard::GetObjectiveInDisplaySlot(const DisplaySlot slot) const
{
    jni::frame f;

    return std::make_unique<ScoreObjective>(jni::make_global(maps::Scoreboard(this->instance).getObjectiveInDisplaySlot.call(static_cast<jint>(slot))));
}

std::vector<std::unique_ptr<ScorePlayerTeam>> Scoreboard::GetTeams() const
{
    jni::frame f;

    std::vector<std::unique_ptr<ScorePlayerTeam>> teamList;

    maps::Collection collection = maps::Scoreboard(this->instance).getTeams.call();
    std::vector<maps::Object> vec = collection.toArray().to_vector();

    for (maps::Object& obj : vec)
    {
        teamList.push_back(std::make_unique<ScorePlayerTeam>(jni::make_global(obj)));
    }

    return teamList;
}

std::vector<std::unique_ptr<Score>> Scoreboard::GetSortedScores(const std::unique_ptr<ScoreObjective>& objective) const
{
    jni::frame f;

    std::vector<std::unique_ptr<Score>> scoreList;

    maps::ScoreObjective objParam(objective->GetInstance());
    maps::Collection collection = maps::Scoreboard(this->instance).getSortedScores.call(objParam);
    std::vector<maps::Object> vec = collection.toArray().to_vector();

    for (maps::Object& obj : vec)
    {
        scoreList.push_back(std::make_unique<Score>(jni::make_global(obj)));
    }

    return scoreList;
}

void Scoreboard::RemoveTeam(const std::unique_ptr<ScorePlayerTeam>& team) const 
{
    jni::frame f;

    maps::ScorePlayerTeam teamParam(team->GetInstance());
    maps::Scoreboard(this->instance).removeTeam.call(teamParam);
}

void Scoreboard::RemovePlayerFromTeam(const std::string& playerName, const std::unique_ptr<ScorePlayerTeam>& team) const
{
    jni::frame f;

    maps::ScorePlayerTeam teamParam(team->GetInstance());
    maps::Scoreboard(this->instance).removePlayerFromTeam.call(JavaUtil::StringToJString(playerName), teamParam);
}

void Scoreboard::SetObjectiveInDisplaySlot(const DisplaySlot slot, const std::unique_ptr<ScoreObjective>& objective) const
{
    jni::frame f;

    maps::ScoreObjective objParam(objective ? objective->GetInstance() : nullptr);
    maps::Scoreboard(this->instance).setObjectiveInDisplaySlot.call(static_cast<jint>(slot), objParam);
}