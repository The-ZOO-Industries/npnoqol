#pragma once

#include <easy_jni/easy_jni.hpp>

#include "score_player_team.hpp"

namespace jni
{
	class scoreboard final : public jni::object
	{
	public:
		explicit scoreboard(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto get_teams() const
			-> std::vector<std::unique_ptr<jni::score_player_team>>
		{
			return get_method<jni::collection>("getTeams")->call()->to_vector<jni::score_player_team>();
		}
	};
}