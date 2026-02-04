#include "Scoreboard.h"

Scoreboard::Scoreboard(const jobject instance)
    : JavaClass(instance)
{

}

Scoreboard::~Scoreboard() = default;

auto Scoreboard::AddPlayerToTeam(const std::string& playerName, const std::string& teamName) const -> bool
{
    jni::frame f;

    return maps::Scoreboard(this->instance).addPlayerToTeam.call(JavaUtil::StringToJString(playerName), JavaUtil::StringToJString(teamName));
}

auto Scoreboard::GetTeam(const std::string& teamName) const -> std::unique_ptr<ScorePlayerTeam>
{
    jni::frame f;

    return std::make_unique<ScorePlayerTeam>(jobject(maps::ScorePlayerTeam(maps::Scoreboard(this->instance).getTeam.call(JavaUtil::StringToJString(teamName)), true)));
}

auto Scoreboard::GetPlayersTeam(const std::string& playerName) const -> std::unique_ptr<ScorePlayerTeam>
{
    jni::frame f;

    return std::make_unique<ScorePlayerTeam>(jobject(maps::ScorePlayerTeam(maps::Scoreboard(this->instance).getPlayersTeam.call(JavaUtil::StringToJString(playerName)), true)));
}

auto Scoreboard::CreateTeam(const std::string& teamName) const -> std::unique_ptr<ScorePlayerTeam>
{
    jni::frame f;

    return std::make_unique<ScorePlayerTeam>(jobject(maps::ScorePlayerTeam(maps::Scoreboard(this->instance).createTeam.call(JavaUtil::StringToJString(teamName)), true)));
}

auto Scoreboard::GetObjectiveInDisplaySlot(const DisplaySlot slot) const -> std::unique_ptr<ScoreObjective>
{
    jni::frame f;

    return std::make_unique<ScoreObjective>(jobject(maps::ScoreObjective(maps::Scoreboard(this->instance).getObjectiveInDisplaySlot.call(static_cast<jint>(slot)), true)));
}

std::vector<std::unique_ptr<ScorePlayerTeam>> Scoreboard::GetTeams() const
{
    jni::frame f;

    std::vector<std::unique_ptr<ScorePlayerTeam>> teamList;

    maps::Collection collection = maps::Scoreboard(this->instance).getTeams.call();

    jni::array<maps::Object> array = collection.toArray.call();

    std::vector<maps::Object> vec = array.to_vector();

    for (maps::Object& obj : vec)
    {
        teamList.push_back(std::make_unique<ScorePlayerTeam>(jobject(maps::ScorePlayerTeam(obj, true))));
    }

    return teamList;
}

auto Scoreboard::GetSortedScores(const std::unique_ptr<ScoreObjective>& objective) const -> std::vector<std::unique_ptr<Score>>
{
    jni::frame f;

    std::vector<std::unique_ptr<Score>> scoreList{};

    maps::ScoreObjective objParam{ jobject(maps::ScoreObjective(objective->GetInstance(), true)) };
    maps::Collection collection = maps::Scoreboard(this->instance).getSortedScores.call(objParam);

    std::vector<maps::Object> vec = maps::Collection(collection, true).toArray.call().to_vector();
    for (maps::Object& obj : vec)
    {
        scoreList.push_back(std::make_unique<Score>(jobject(maps::Score(obj, true))));
    }

    return scoreList;
}

auto Scoreboard::RemoveTeam(const std::unique_ptr<ScorePlayerTeam>& team) const -> void
{
    jni::frame f;

    maps::ScorePlayerTeam teamParam{ jobject(maps::ScorePlayerTeam(team->GetInstance(), true)) };
    maps::Scoreboard(this->instance).removeTeam.call(teamParam);
}

auto Scoreboard::RemovePlayerFromTeam(const std::string& playerName, const std::unique_ptr<ScorePlayerTeam>& team) const -> void
{
    jni::frame f;

    maps::ScorePlayerTeam teamParam{ jobject(maps::ScorePlayerTeam(team->GetInstance(), true)) };
    maps::Scoreboard(this->instance).removePlayerFromTeam.call(JavaUtil::StringToJString(playerName), teamParam);
}

auto Scoreboard::SetObjectiveInDisplaySlot(const DisplaySlot slot, const std::unique_ptr<ScoreObjective>& objective) const -> void
{
    jni::frame f;

    maps::ScoreObjective objParam{ jobject(objective ? maps::ScoreObjective(objective->GetInstance(), true) : nullptr) };
    maps::Scoreboard(this->instance).setObjectiveInDisplaySlot.call(static_cast<jint>(slot), objParam);
}