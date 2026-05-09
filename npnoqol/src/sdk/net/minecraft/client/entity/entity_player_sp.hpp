#pragma once

#include "../../entity/player/entity_player.hpp"
#include "../../util/i_chat_component.hpp"

namespace sdk
{
	class entity_player_sp : public sdk::entity_player
	{
	public:
		explicit entity_player_sp(const vmhook::oop_type_t instance) noexcept
			: sdk::entity_player{ instance }
		{

		}

		auto send_chat_message(const std::string& message) const noexcept
			-> void
		{
			get_method(mapping::entity_player_sp::sendChatMessage)->call(message);
		}

		auto add_chat_message(const std::unique_ptr<sdk::i_chat_component>& chat_component) const noexcept
			-> void
		{
			get_method(mapping::entity_player_sp::addChatMessage)->call(chat_component);
		}
	};
}