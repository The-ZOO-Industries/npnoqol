#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/net/minecraft/world/storage/WorldInfo/WorldInfo.h"
#include "../../src/wrapper/sdk/net/minecraft/entity/player/EntityPlayer/EntityPlayer.h"
#include "../../src/wrapper/sdk/java/util/List/List.h"

class World : public JavaClass
{
public:
    explicit World(maps::World instance);

    virtual ~World() override;

    [[nodiscard]] virtual std::unique_ptr<WorldInfo> GetWorldInfo() const final;

    [[nodiscard]] virtual std::vector<std::unique_ptr<EntityPlayer>> GetPlayerEntities() const final;
};