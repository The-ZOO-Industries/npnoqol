#pragma once

#include "../../world/world.hpp"

#include "../scoreboard/scoreboard.hpp"
#include "../../entity/player/entity_player.hpp"

namespace jni
{
	class world_client final : public jni::world
	{
	public:
		explicit world_client(const jobject instance)
			: world{ instance }
		{

		}

		auto get_scoreboard() const
			-> std::unique_ptr<jni::scoreboard>
		{
			return get_method<jni::scoreboard>("getScoreboard")->call();
		}

		auto get_player_entity_by_name(const std::string& value) const
			-> std::unique_ptr<jni::entity_player>
		{
			return get_method<jni::entity_player>("getPlayerEntityByName")->call(value);
		}
	};
}