#include "JavaClass.h"

#include <print>

JavaClass::JavaClass(maps::Object instance)
    : instance{ instance }
{

}

JavaClass::~JavaClass() = default;

maps::Object JavaClass::GetInstance() const
{
    return this->instance;
}