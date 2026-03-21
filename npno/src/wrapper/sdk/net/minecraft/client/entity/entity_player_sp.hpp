#pragma once

#include "../../entity/player/entity_player.hpp"

#include "../../util/chat_component_text.hpp"
#include "../network/net_handler_play_client.hpp"

namespace jni
{
	class entity_player_sp final : public jni::entity_player
	{
	public:
		explicit entity_player_sp(const jobject instance)
			: jni::entity_player{ instance }
		{

		}

		auto send_chat_message(const std::string& value)
			-> void
		{
			get_method<void, std::string>(mapping::entity_player_sp::sendChatMessage)->call(value);
		}

		auto add_chat_message(const std::unique_ptr<jni::i_chat_component>& value)
			-> void
		{
			get_method<void, jni::i_chat_component>(mapping::entity_player_sp::addChatMessage)->call(value);
		}

		auto get_send_queue() const
			-> std::unique_ptr<jni::net_handler_play_client>
		{
			return get_field<jni::net_handler_play_client>(mapping::entity_player_sp::sendQueue)->get();
		}
	};
}