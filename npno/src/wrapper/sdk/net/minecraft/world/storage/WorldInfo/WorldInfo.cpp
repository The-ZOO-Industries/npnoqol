#include "WorldInfo.h"

#include "../../src/wrapper/sdk/java/util/List/List.h"

WorldInfo::WorldInfo(const jobject instance)
    : JavaClass(instance)
{
    this->Init();
}

WorldInfo::~WorldInfo() = default;

I64 WorldInfo::GetRandomSeed() const
{
    return static_cast<I64>(Jvm::env->GetLongField(this->instance, randomSeedFieldID));
}

I64 WorldInfo::GetWorldTime() const
{
    return static_cast<I64>(Jvm::env->GetLongField(this->instance, worldTimeFieldID));
}

std::string WorldInfo::GetWorldName() const
{
    jni::frame f;
    
    return JavaUtil::JStringToString(static_cast<jstring>(Jvm::env->GetObjectField(this->instance, worldNameFieldID)));
}