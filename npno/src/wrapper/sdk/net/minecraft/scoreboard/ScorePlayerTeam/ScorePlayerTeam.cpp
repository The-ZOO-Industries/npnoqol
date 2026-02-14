#include "ScorePlayerTeam.h"

ScorePlayerTeam::ScorePlayerTeam(maps::ScorePlayerTeam instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

ScorePlayerTeam::~ScorePlayerTeam() = default;

std::string ScorePlayerTeam::GetTeamName() const
{
    maps::String teamName = maps::ScorePlayerTeam(this->instance.object_instance).getTeamName.call();
    return JavaUtil::JStringToString((jstring)jobject(teamName));
}

std::string ScorePlayerTeam::GetNamePrefix() const
{
    maps::String prefix = maps::ScorePlayerTeam(this->instance.object_instance).getColorPrefix.call();
    return JavaUtil::JStringToString((jstring)jobject(prefix));
}

std::string ScorePlayerTeam::GetNameSuffix() const
{
    maps::String suffix = maps::ScorePlayerTeam(this->instance.object_instance).getColorSuffix.call();
    return JavaUtil::JStringToString((jstring)jobject(suffix));
}

std::vector<std::string> ScorePlayerTeam::GetMembershipCollection() const
{
    std::vector<std::string> members;

    maps::Collection collection = maps::ScorePlayerTeam(this->instance.object_instance).getMembershipCollection.call();
    jni::array<maps::Object> array = collection.toArray.call();
    std::vector<maps::Object> vec = array.to_vector();

    for (maps::Object& obj : vec)
    {
        members.push_back(JavaUtil::JStringToString(static_cast<jstring>(static_cast<jobject>(obj))));
    }

    return members;
}

void ScorePlayerTeam::SetNamePrefix(const std::string& prefix) const
{
    jstring jPrefix = JavaUtil::StringToJString(prefix);
    maps::String prefixStr{ jPrefix };
    maps::ScorePlayerTeam(this->instance.object_instance).setNamePrefix.call(prefixStr);
}

void ScorePlayerTeam::SetNameSuffix(const std::string& suffix) const
{
    jstring jSuffix = JavaUtil::StringToJString(suffix);
    maps::String suffixStr{ jSuffix };
    maps::ScorePlayerTeam(this->instance.object_instance).setNameSuffix.call(suffixStr);
}