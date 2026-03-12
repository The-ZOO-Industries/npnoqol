#pragma once

#include "../../entity/player/entity_player.hpp"

#include "../../util/chat_component_text.hpp"

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
			get_method<void, std::string>("sendChatMessage")->call(value);
		}

		auto add_chat_message(const std::unique_ptr<jni::i_chat_component>& value)
			-> void
		{
			get_method<void, jni::i_chat_component>("addChatMessage")->call(value);
		}
	};
}