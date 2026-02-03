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