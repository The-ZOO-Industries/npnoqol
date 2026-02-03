#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

class Score final : public JavaClass
{
public:
	explicit Score(const jobject instance);

	virtual ~Score() override;

	[[nodiscard]] I32 GetScorePoints() const;

	[[nodiscard]] std::string GetPlayerName() const;
};

namespace maps
{
    BEGIN_KLASS_DEF(Score, "net/minecraft/scoreboard/Score")
        jni::method<jint, "getScorePoints"> getScorePoints{ *this };
        jni::method<String, "getPlayerName"> getPlayerName{ *this };
    END_KLASS_DEF()
}