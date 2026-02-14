#include "Collection.h"

Collection::Collection(maps::Collection instance) 
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

Collection::~Collection() = default;

jint Collection::Size() const 
{
    return maps::Collection(this->instance.object_instance).size.call();
}

jni::array<maps::Object> Collection::ToArray() const
{
    return maps::Collection(this->instance).toArray.call();
}