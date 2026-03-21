#pragma once

#include <easy_jni/easy_jni.hpp>

#include "network_player_info.hpp"

namespace jni
{
	class net_handler_play_client final : public jni::object
	{
	public:
		explicit net_handler_play_client(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto get_player_info_map() const
			-> std::vector<std::unique_ptr<jni::network_player_info>>
		{
			return get_method<jni::collection>(mapping::net_handler_play_client::getPlayerInfoMap)->call()->to_vector<jni::network_player_info>();
		}
	};
}