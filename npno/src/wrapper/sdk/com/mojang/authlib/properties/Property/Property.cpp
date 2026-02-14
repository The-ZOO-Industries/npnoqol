#include "Property.h"

Property::Property(maps::Property instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

Property::~Property() = default;

std::string Property::GetValue() const
{
    maps::String value = maps::Property(this->instance.object_instance).getValue.call();
    return JavaUtil::JStringToString((jstring)jobject(value));
}

std::string Property::GetName() const
{
    maps::String name = maps::Property(this->instance.object_instance).getName.call();
    return JavaUtil::JStringToString((jstring)jobject(name));
}