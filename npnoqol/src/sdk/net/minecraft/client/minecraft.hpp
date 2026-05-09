#pragma once

#include "../../../mapping.hpp"

#include "../client/entity/entity_player_sp.hpp"
#include "../client/gui/gui_ingame.hpp"
#include "../client/multiplayer/world_client.hpp"
#include "../util/chat_component_text.hpp"

namespace sdk
{
	class minecraft final : public vmhook::object<sdk::minecraft>
	{
	public:
		explicit minecraft(const vmhook::oop_type_t instance) noexcept
			: vmhook::object<sdk::minecraft>{ instance }
		{

		}

		static auto get_minecraft() noexcept
			-> std::unique_ptr<sdk::minecraft>
		{
			return get_field(mapping::minecraft::theMinecraft)->get();
		}

		auto get_the_player() const noexcept
			-> std::unique_ptr<sdk::entity_player_sp>
		{
			return get_field(mapping::minecraft::thePlayer)->get();
		}

		auto get_the_world() const noexcept
			-> std::unique_ptr<sdk::world_client>
		{
			return get_field(mapping::minecraft::theWorld)->get();
		}

		auto get_ingame_gui() const noexcept
			-> std::unique_ptr<sdk::gui_ingame>
		{
			return get_field(mapping::minecraft::ingameGUI)->get();
		}
	};
}
