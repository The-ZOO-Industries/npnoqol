#include "WorldInfo.h"

WorldInfo::WorldInfo(maps::WorldInfo instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

WorldInfo::~WorldInfo() = default;

I64 WorldInfo::GetRandomSeed() const
{
    return static_cast<I64>(maps::WorldInfo(this->instance.object_instance).randomSeed.get());
}

I64 WorldInfo::GetWorldTime() const
{
    return static_cast<I64>(maps::WorldInfo(this->instance.object_instance).worldTime.get());
}

std::string WorldInfo::GetWorldName() const
{
    maps::String worldName = maps::WorldInfo(this->instance.object_instance).worldName.get();
    return JavaUtil::JStringToString((jstring)jobject(worldName));
}