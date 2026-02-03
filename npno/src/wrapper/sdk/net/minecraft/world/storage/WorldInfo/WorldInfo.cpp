#include "WorldInfo.h"

WorldInfo::WorldInfo(const jobject instance)
    : JavaClass(instance)
{

}

WorldInfo::~WorldInfo() = default;

I64 WorldInfo::GetRandomSeed() const
{
    return static_cast<I64>(maps::WorldInfo(this->instance).randomSeed.get());
}

I64 WorldInfo::GetWorldTime() const
{
    return static_cast<I64>(maps::WorldInfo(this->instance).worldTime.get());
}

std::string WorldInfo::GetWorldName() const
{
    jni::frame f;

    return JavaUtil::JStringToString((jstring)jobject(maps::WorldInfo(this->instance).worldName.get()));
}