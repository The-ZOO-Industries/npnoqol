#pragma once

#include "../../feature.hpp"
#include "../../../sdk/net/minecraft/client/multiplayer/world_client.hpp"

namespace zoo
{
	class module : public zoo::feature
	{
	public:
		module() noexcept;

		virtual ~module() noexcept;

		virtual auto on_run_tick() noexcept
			-> void = 0;

		virtual auto on_minecraft_tick() noexcept
			-> void;

		virtual auto on_print_chat_message(vmhook::return_value& return_value, const std::unique_ptr<sdk::i_chat_component>& chat_component) noexcept
			-> bool;

		virtual auto on_load_world(const std::unique_ptr<sdk::minecraft>& minecraft) noexcept
			-> void;
	};
}
