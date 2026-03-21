#pragma once

#include "../../world/world.hpp"

#include "../../scoreboard/scoreboard.hpp"
#include "../../entity/player/entity_player.hpp"

namespace jni
{
	class world_client final : public jni::world
	{
	public:
		explicit world_client(const jobject instance)
			: jni::world{ instance }
		{

		}

		auto get_scoreboard() const
			-> std::unique_ptr<jni::scoreboard>
		{
			return get_method<jni::scoreboard>(mapping::world_client::getScoreboard)->call();
		}

		auto get_player_entity_by_name(const std::string& value) const
			-> std::unique_ptr<jni::entity_player>
		{
			return get_method<jni::entity_player, std::string>(mapping::world_client::getPlayerEntityByName)->call(value);
		}

		auto add_entity_to_world(const int id, const std::unique_ptr<jni::entity>& entity) const
			-> void
		{
			get_method<void, int, jni::entity>(mapping::world_client::addEntityToWorld)->call(id, entity);
		}
	};
}