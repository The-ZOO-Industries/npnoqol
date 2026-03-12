#pragma once

#include "../wrapper/sdk/net/minecraft/client/minecraft.hpp"

#include "../util/config.hpp"
#include "../util/enum_chat_formatting.hpp"
#include "../util/hypixel_api.hpp"
#include "../util/hypixel_gametype.hpp"
#include "../util/hypixel_mode.hpp"
#include "../util/network.hpp"

#include <format>
#include <print>
#include <sstream>
#include <mutex>
#include <regex>

namespace npno
{
	class feature
	{
	public:
		feature();

		virtual ~feature();

		virtual auto update()
			-> void = 0;

		virtual auto sanity_check() const 
			-> bool;

		virtual auto is_bot(const std::unique_ptr<jni::entity_player>& entity) const
			-> bool final;

	protected:
		inline static std::unique_ptr<jni::minecraft> mc{};
	};

	struct hook_handler
	{
		bool detected{ false };

		virtual auto clear() ->
			void
		{
			this->detected = false;
		}
	};
}