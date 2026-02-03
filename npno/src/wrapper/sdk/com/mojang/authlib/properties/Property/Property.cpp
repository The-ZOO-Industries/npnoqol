#include "Property.h"

Property::Property(const jobject instance)
    : JavaClass(instance)
{

}

Property::~Property() = default;

std::string Property::GetValue() const
{
    jni::frame f;

    return JavaUtil::JStringToString(static_cast<jstring>(maps::Property(this->instance).getValue.call()));
}

std::string Property::GetName() const
{
    jni::frame f;

    return JavaUtil::JStringToString(static_cast<jstring>(maps::Property(this->instance).getName.call()));
}