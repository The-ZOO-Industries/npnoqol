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
    explicit JavaClass(maps::Object instance);
    virtual ~JavaClass();

    [[nodiscard]] maps::Object GetInstance() const;

protected:
    maps::Object instance;
};