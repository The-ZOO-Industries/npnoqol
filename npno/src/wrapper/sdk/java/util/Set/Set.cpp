#include "Set.h"

Set::Set(maps::Set instance)
    : Collection(maps::Collection(instance.object_instance, instance.is_global()))
{

}

Set::~Set() = default;