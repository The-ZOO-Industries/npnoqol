#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/net/minecraft/world/storage/WorldInfo/WorldInfo.h"
#include "../../src/wrapper/sdk/net/minecraft/entity/player/EntityPlayer/EntityPlayer.h"

class World : public JavaClass
{
public:
	explicit World(const jobject instance);

	virtual ~World() override;

	[[nodiscard]] virtual std::unique_ptr<WorldInfo> GetWorldInfo() const final;

	[[nodiscard]] virtual std::vector<std::unique_ptr<EntityPlayer>> GetPlayerEntities() const final;
};

namespace maps
{
	BEGIN_KLASS_DEF(World, "net/minecraft/world/storage/WorldInfo")
        jni::field<WorldInfo, "worldInfo"> worldInfo{ *this };
        jni::field<List, "playerEntities"> playerEntities{ *this };
    END_KLASS_DEF()
}