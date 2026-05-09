#pragma once

#include "net/minecraft/client/minecraft.hpp"
#include "net/minecraft/client/multiplayer/world_client.hpp"
#include "net/minecraft/entity/entity.hpp"
#include "net/minecraft/entity/entity_living_base.hpp"
#include "net/minecraft/entity/player/entity_player.hpp"
#include "net/minecraft/world.hpp"
#include "mapping.hpp"

#include <vmhook/vmhook.hpp>

namespace sdk
{
	static auto register_classes() noexcept
		-> void
	{
		// minecraft class is already registered in mapping::can_inject, so we don't need to register it again here

		vmhook::register_class<sdk::entity>(mapping::entity::clazz);
		vmhook::register_class<sdk::entity_living_base>(mapping::entity_living_base::clazz);
		vmhook::register_class<sdk::entity_player>(mapping::entity_player::clazz);
		vmhook::register_class<sdk::entity_player_sp>(mapping::entity_player_sp::clazz);
		vmhook::register_class<sdk::world>(mapping::world::clazz);
		vmhook::register_class<sdk::world_client>(mapping::world_client::clazz);
		vmhook::register_class<sdk::gui_ingame>(mapping::gui_ingame::clazz);
		vmhook::register_class<sdk::gui_new_chat>(mapping::gui_new_chat::clazz);
		vmhook::register_class<sdk::chat_component_text>(mapping::chat_component_text::clazz);
		vmhook::register_class<sdk::i_chat_component>(mapping::i_chat_component::clazz);
	}
}
