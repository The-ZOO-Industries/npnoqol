#include "ScoreObjective.h"

ScoreObjective::ScoreObjective(const jobject instance)
    : JavaClass(instance)
{

}

ScoreObjective::~ScoreObjective() = default;

auto ScoreObjective::GetName() const -> std::string
{
    jni::frame f;

    return JavaUtil::JStringToString((jstring)jobject(maps::ScoreObjective(this->instance).getName.call()));
}

auto ScoreObjective::GetDisplayName() const -> std::string
{
    jni::frame f;

    return JavaUtil::JStringToString((jstring)jobject(maps::ScoreObjective(this->instance).getDisplayName.call()));
}

auto ScoreObjective::SetDisplayName(const std::string& name) const -> void
{
    jni::frame f;

    maps::ScoreObjective(this->instance).setDisplayName.call(JavaUtil::StringToJString(name));
}