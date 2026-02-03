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

namespace maps
{
    BEGIN_KLASS_DEF(UUID, "java/util/UUID")
        jni::method<jint, "version"> version{ *this };
        jni::method<String, "toString"> toString{ *this };
    END_KLASS_DEF()
}