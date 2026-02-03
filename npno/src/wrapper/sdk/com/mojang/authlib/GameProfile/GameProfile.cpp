#include "GameProfile.h"

GameProfile::GameProfile(const jobject instance)
    : JavaClass(instance)
{

}

GameProfile::~GameProfile() = default;

std::string GameProfile::GetName() const
{
    jni::frame f;

    return JavaUtil::JStringToString((jstring)jobject(maps::GameProfile(this->instance).getName.call()));
}

std::unique_ptr<PropertyMap> GameProfile::GetProperties() const
{
    jni::frame f;

    jobject local = jobject(maps::GameProfile(this->instance).getProperties.call());
    return std::make_unique<PropertyMap>(jobject(maps::PropertyMap(local, true)));
}