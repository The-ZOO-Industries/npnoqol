#include "List.h"

List::List(maps::List instance)
    : Collection(maps::Collection(instance.object_instance, instance.is_global()))
{

}

List::~List() = default;

maps::Object List::Get(const jint index) const
{
    return maps::List(this->instance.object_instance).get.call(index);
}