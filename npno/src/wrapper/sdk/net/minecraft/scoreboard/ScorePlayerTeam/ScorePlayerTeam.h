#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

class ScorePlayerTeam final : public JavaClass
{
public:
	explicit ScorePlayerTeam(const jobject instance);

	virtual ~ScorePlayerTeam() override;

	[[nodiscard]] std::string GetNamePrefix() const;
	[[nodiscard]] std::string GetNameSuffix() const;
	[[nodiscard]] std::string GetTeamName() const;

	[[nodiscard]] std::vector<std::string> GetMembershipCollection() const;

	void SetNamePrefix(const std::string& prefix) const;
	void SetNameSuffix(const std::string& suffix) const;
};

namespace maps
{
    BEGIN_KLASS_DEF(ScorePlayerTeam, "net/minecraft/scoreboard/ScorePlayerTeam")
        jni::method<String, "getColorPrefix"> getColorPrefix{ *this };
        jni::method<String, "getColorSuffix"> getColorSuffix{ *this };
        jni::method<String, "getTeamName"> getTeamName{ *this };
        jni::method<Collection, "getMembershipCollection"> getMembershipCollection{ *this };
        jni::method<void, "setNamePrefix", jni::NOT_STATIC, String> setNamePrefix{ *this };
        jni::method<void, "setNameSuffix", jni::NOT_STATIC, String> setNameSuffix{ *this };
    END_KLASS_DEF()
}