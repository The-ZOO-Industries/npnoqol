#include "ScorePlayerTeam.h"

ScorePlayerTeam::ScorePlayerTeam(const jobject instance)
    : JavaClass(instance)
{

}

ScorePlayerTeam::~ScorePlayerTeam() = default;

std::string ScorePlayerTeam::GetTeamName() const 
{
    jni::frame f;

    return JavaUtil::JStringToString(static_cast<jstring>(maps::ScorePlayerTeam(this->instance).getTeamName.call()));
}

std::string ScorePlayerTeam::GetNamePrefix() const 
{
    jni::frame f;

    return JavaUtil::JStringToString(static_cast<jstring>(maps::ScorePlayerTeam(this->instance).getColorPrefix.call()));
}

std::string ScorePlayerTeam::GetNameSuffix() const 
{
    jni::frame f;

    return JavaUtil::JStringToString(static_cast<jstring>(maps::ScorePlayerTeam(this->instance).getColorSuffix.call()));
}

std::vector<std::string> ScorePlayerTeam::GetMembershipCollection() const
{
    jni::frame f;

    std::vector<std::string> members;

    maps::Collection collection = maps::ScorePlayerTeam(this->instance).getMembershipCollection.call();
    std::vector<maps::Object> vec = collection.toArray().to_vector();

    for (maps::Object& obj : vec)
    {
        members.push_back(JavaUtil::JStringToString(static_cast<jstring>(static_cast<jobject>(obj))));
    }

    return members;
}

void ScorePlayerTeam::SetNamePrefix(const std::string& prefix) const
{
    jni::frame f;

    maps::ScorePlayerTeam(this->instance).setNamePrefix.call(JavaUtil::StringToJString(prefix));
}

void ScorePlayerTeam::SetNameSuffix(const std::string& suffix) const
{
    jni::frame f;
    
    maps::ScorePlayerTeam(this->instance).setNameSuffix.call(JavaUtil::StringToJString(suffix));
}