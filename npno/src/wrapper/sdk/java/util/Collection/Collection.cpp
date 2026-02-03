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
    return static_cast<jobjectArray>(maps::Collection(this->instance).toArray.call());
}