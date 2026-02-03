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