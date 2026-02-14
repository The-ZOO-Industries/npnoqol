#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

class WorldInfo : public JavaClass
{
public:
    explicit WorldInfo(maps::WorldInfo instance);

    virtual ~WorldInfo() override;

    [[nodiscard]] I64 GetRandomSeed() const;
    [[nodiscard]] I64 GetWorldTime() const;

    [[nodiscard]] std::string GetWorldName() const;
};