#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

class Property final : public JavaClass
{
public:
    explicit Property(const jobject instance);

    virtual ~Property() override;

    [[nodiscard]] std::string GetValue() const;
    [[nodiscard]] std::string GetName() const;
};

namespace maps
{
    BEGIN_KLASS_DEF(Property, "com/mojang/authlib/properties/Property")
        jni::method<String, "getValue"> getValue{ *this };
        jni::method<String, "getName"> getName{ *this };
    END_KLASS_DEF()
}