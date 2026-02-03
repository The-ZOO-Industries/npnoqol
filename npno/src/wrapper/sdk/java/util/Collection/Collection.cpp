#include "Collection.h"

Collection::Collection(const jobject instance) : 
    JavaClass(instance) 
{

}

Collection::~Collection() = default;

jint Collection::Size() const 
{
    return maps::Collection(this->instance).size.call();
}

jobjectArray Collection::ToArray() const 
{
    return (jobjectArray)jobject(maps::Collection(this->instance).toArray.call());
}