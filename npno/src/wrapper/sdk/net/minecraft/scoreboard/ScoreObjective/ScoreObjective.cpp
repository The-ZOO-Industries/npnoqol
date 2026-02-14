#include "ScoreObjective.h"

ScoreObjective::ScoreObjective(maps::ScoreObjective instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

ScoreObjective::~ScoreObjective() = default;

std::string ScoreObjective::GetName() const
{
    maps::String name = maps::ScoreObjective(this->instance.object_instance).getName.call();
    return JavaUtil::JStringToString((jstring)jobject(name));
}

std::string ScoreObjective::GetDisplayName() const
{
    maps::String displayName = maps::ScoreObjective(this->instance.object_instance).getDisplayName.call();
    return JavaUtil::JStringToString((jstring)jobject(displayName));
}

void ScoreObjective::SetDisplayName(const std::string& name) const
{
    jstring jName = JavaUtil::StringToJString(name);
    maps::String nameStr{ jName };
    maps::ScoreObjective(this->instance.object_instance).setDisplayName.call(nameStr);
}