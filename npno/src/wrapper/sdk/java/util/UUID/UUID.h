#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

class UUID_J final : public JavaClass
{
public:
    explicit UUID_J(const jobject instance);

    virtual ~UUID_J() override;

    [[nodiscard]] jint Version() const;

    [[nodiscard]] jstring ToString() const;
};