#pragma once

#include <easy_jni/easy_jni.hpp>

#include "../../../../com/mojang/authlib/game_profile.hpp"
#include "../../util/i_chat_component.hpp"

namespace jni
{
	class network_player_info final : public jni::object
	{
	public:
		explicit network_player_info(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto get_game_profile() const
			-> std::unique_ptr<jni::game_profile>
		{
			return get_method<jni::game_profile>("getGameProfile")->call();
		}

		auto get_display_name() const
			-> std::unique_ptr<jni::i_chat_component>
		{
			return get_method<jni::i_chat_component>("getDisplayName")->call();
		}

		auto set_display_name(const std::unique_ptr<jni::i_chat_component>& value) const
			-> void
		{
			get_method<void, jni::i_chat_component>("setDisplayName")->call(value);
		}
	};
}