#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

class ScoreObjective final : public JavaClass
{
public:
	explicit ScoreObjective(const jobject instance);

	virtual ~ScoreObjective() override;

	[[nodiscard]] std::string GetName() const;
	[[nodiscard]] std::string GetDisplayName() const;

	void SetDisplayName(const std::string& name) const;
};

namespace maps
{
    BEGIN_KLASS_DEF(ScoreObjective, "net/minecraft/scoreboard/ScoreObjective")
        jni::method<String, "getName"> getName{ *this };
        jni::method<String, "getDisplayName"> getDisplayName{ *this };
        jni::method<void, "setDisplayName", jni::NOT_STATIC, String> setDisplayName{ *this };
    END_KLASS_DEF()
}