#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/com/mojang/authlib/properties/Property/Property.h"

class PropertyMap final : public JavaClass
{
public:
    explicit PropertyMap(const jobject instance);

    virtual ~PropertyMap() override;

    [[nodiscard]] std::vector<std::unique_ptr<Property>> GetValues() const;
};

namespace maps
{
    BEGIN_KLASS_DEF(PropertyMap, "com/mojang/authlib/properties/PropertyMap")
        jni::method<Collection, "values"> values{ *this };
    END_KLASS_DEF()
}