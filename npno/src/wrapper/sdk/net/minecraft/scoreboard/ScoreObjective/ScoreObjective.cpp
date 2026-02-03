#include "ScoreObjective.h"

ScoreObjective::ScoreObjective(const jobject instance)
	: JavaClass(instance)
{

}

ScoreObjective::~ScoreObjective() = default;

std::string ScoreObjective::GetName() const
{
	jni::frame f;

	return JavaUtil::JStringToString(static_cast<jstring>(maps::ScoreObjective(this->instance).getName.call()));
}

std::string ScoreObjective::GetDisplayName() const
{
	jni::frame f;

	return JavaUtil::JStringToString(static_cast<jstring>(maps::ScoreObjective(this->instance).getDisplayName.call()));
}

void ScoreObjective::SetDisplayName(const std::string& name) const
{
	jni::frame f;
	
	maps::ScoreObjective(this->instance).setDisplayName.call(JavaUtil::StringToJString(name));
}