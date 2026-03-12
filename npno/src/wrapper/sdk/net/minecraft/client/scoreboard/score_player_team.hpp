#pragma once

#include <easy_jni/easy_jni.hpp>

namespace jni
{
	class score_player_team final : public jni::object
	{
	public:
		explicit score_player_team(const jobject instance)
			: jni::object{ instance }
		{

		}
	};
}