#include "Score.h"

Score::Score(const jobject instance)
	: JavaClass(instance)
{

}

Score::~Score() = default;

I32 Score::GetScorePoints() const
{
	return static_cast<I32>(maps::Score(this->instance).getScorePoints.call());
}

std::string Score::GetPlayerName() const
{
	jni::frame f;

	return JavaUtil::JStringToString(static_cast<jstring>(maps::Score(this->instance).getPlayerName.call()));
}