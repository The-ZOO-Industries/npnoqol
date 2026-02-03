#include "List.h"

List::List(const jobject instance)
	: Collection(instance)
{
	
}

List::~List() = default;

jobject List::Get(const jint index) const
{
    jni::frame f;

    return jobject(maps::List(this->instance).get.call(index));
}