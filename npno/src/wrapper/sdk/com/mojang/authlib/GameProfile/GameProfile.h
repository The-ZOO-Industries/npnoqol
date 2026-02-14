#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/com/mojang/authlib/properties/PropertyMap/PropertyMap.h"

class GameProfile final : public JavaClass
{
public:
    explicit GameProfile(maps::GameProfile instance);

    virtual ~GameProfile() override;

    [[nodiscard]] std::string GetName() const;
    [[nodiscard]] std::unique_ptr<PropertyMap> GetProperties() const;
};