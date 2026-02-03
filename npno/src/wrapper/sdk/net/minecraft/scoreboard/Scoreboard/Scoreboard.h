#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/net/minecraft/scoreboard/Score/Score.h"
#include "../../src/wrapper/sdk/net/minecraft/scoreboard/ScoreObjective/ScoreObjective.h"
#include "../../src/wrapper/sdk/net/minecraft/scoreboard/ScorePlayerTeam/ScorePlayerTeam.h"

class Scoreboard final : public JavaClass
{
public:
	explicit Scoreboard(const jobject instance);

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

namespace maps
{
	BEGIN_KLASS_DEF(Scoreboard, "net/minecraft/scoreboard/Scoreboard")
        jni::method<jboolean, "addPlayerToTeam", jni::NOT_STATIC, String, String> addPlayerToTeam{ *this };
        jni::method<ScorePlayerTeam, "getTeam", jni::NOT_STATIC, String> getTeam{ *this };
        jni::method<ScorePlayerTeam, "getPlayersTeam", jni::NOT_STATIC, String> getPlayersTeam{ *this };
        jni::method<ScorePlayerTeam, "createTeam", jni::NOT_STATIC, String> createTeam{ *this };
        jni::method<ScoreObjective, "getObjectiveInDisplaySlot", jni::NOT_STATIC, jint> getObjectiveInDisplaySlot{ *this };
        jni::method<Collection, "getTeams"> getTeams{ *this };
        jni::method<Collection, "getSortedScores", jni::NOT_STATIC, ScoreObjective> getSortedScores{ *this };
        jni::method<void, "removeTeam", jni::NOT_STATIC, ScorePlayerTeam> removeTeam{ *this };
        jni::method<void, "removePlayerFromTeam", jni::NOT_STATIC, String, ScorePlayerTeam> removePlayerFromTeam{ *this };
        jni::method<void, "setObjectiveInDisplaySlot", jni::NOT_STATIC, jint, ScoreObjective> setObjectiveInDisplaySlot{ *this };
    END_KLASS_DEF()
}