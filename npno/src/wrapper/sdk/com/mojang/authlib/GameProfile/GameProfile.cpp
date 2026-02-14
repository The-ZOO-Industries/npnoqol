#include "GameProfile.h"

GameProfile::GameProfile(maps::GameProfile instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

GameProfile::~GameProfile() = default;

std::string GameProfile::GetName() const
{
    maps::String name = maps::GameProfile(this->instance.object_instance).getName.call();
    return JavaUtil::JStringToString((jstring)jobject(name));
}

std::unique_ptr<PropertyMap> GameProfile::GetProperties() const
{
    maps::PropertyMap properties = maps::GameProfile(this->instance.object_instance).getProperties.call();
    maps::PropertyMap globalProperties{ properties.object_instance, true };
    return std::make_unique<PropertyMap>(globalProperties);
}