#include "GameProfile.h"

GameProfile::GameProfile(const jobject instance)
    : JavaClass(instance)
{

}

GameProfile::~GameProfile() = default;

std::string GameProfile::GetName() const
{
    jni::frame f;
    
    return JavaUtil::JStringToString(static_cast<jstring>(maps::GameProfile(this->instance).getName.call()));
}

std::unique_ptr<PropertyMap> GameProfile::GetProperties() const
{
    jni::frame f;

    return std::make_unique<PropertyMap>(jni::make_global(maps::GameProfile(this->instance).getProperties.call()));
}