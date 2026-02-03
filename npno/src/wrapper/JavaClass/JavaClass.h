#pragma once

#include "../mappings.hpp"
#include "../JavaUtil/JavaUtil.h"

#include <memory>
#include <mutex>

#include <jni/jni.h>
#include <npno/Type.hpp>

class JavaClass
{
public:
    JavaClass(const jobject instance);

    virtual ~JavaClass();

    [[nodiscard]] jobject GetInstance() const;

protected:
    jobject instance;
};