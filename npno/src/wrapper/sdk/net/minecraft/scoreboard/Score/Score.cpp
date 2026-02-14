#include "Score.h"

Score::Score(maps::Score instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

Score::~Score() = default;

I32 Score::GetScorePoints() const
{
    return static_cast<I32>(maps::Score(this->instance.object_instance).getScorePoints.call());
}

std::string Score::GetPlayerName() const
{
    maps::String playerName = maps::Score(this->instance.object_instance).getPlayerName.call();
    return JavaUtil::JStringToString((jstring)jobject(playerName));
}