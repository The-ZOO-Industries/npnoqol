#include "JavaClass.h"

#include <print>

JavaClass::JavaClass(const jobject instance)
    : instance{ instance ? Jvm::env->NewGlobalRef(instance) : nullptr }
{
    
}

JavaClass::~JavaClass()
{
    if (this->instance) Jvm::env->DeleteGlobalRef(this->instance);
}

jobject JavaClass::GetInstance() const
{
    return this->instance;
}