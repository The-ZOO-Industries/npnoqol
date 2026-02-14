#include "UUID.h"

UUID_J::UUID_J(maps::UUID instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

UUID_J::~UUID_J() = default;

jint UUID_J::Version() const
{
    return maps::UUID(this->instance.object_instance).version.call();
}

jstring UUID_J::ToString() const
{
    maps::String str = maps::UUID(this->instance.object_instance).toString.call();
    return (jstring)jobject(str);
}