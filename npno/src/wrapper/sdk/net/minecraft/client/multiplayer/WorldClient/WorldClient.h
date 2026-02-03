#pragma once

#include "../../src/wrapper/sdk/net/minecraft/world/World/World.h"

#include "../../src/wrapper/sdk/net/minecraft/scoreboard/Scoreboard/Scoreboard.h"
#include "../../src/wrapper/sdk/net/minecraft/entity/player/EntityPlayer/EntityPlayer.h"

class WorldClient final : public World
{
public:
	explicit WorldClient(const jobject instance);

	virtual ~WorldClient() override;

	[[nodiscard]] std::unique_ptr<Scoreboard> GetScoreboard() const;
	[[nodiscard]] std::unique_ptr<EntityPlayer> GetPlayerEntityByName(const std::string& name) const;
};

namespace maps
{
    BEGIN_KLASS_DEF_EX(WorldClient, "net/minecraft/client/multiplayer/WorldClient", World)
        jni::method<Scoreboard, "getScoreboard"> getScoreboard{ *this };
        jni::method<EntityPlayer, "getPlayerEntityByName", jni::NOT_STATIC, String> getPlayerEntityByName{ *this };
    END_KLASS_DEF()
}