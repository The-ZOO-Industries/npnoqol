#pragma once

#include "../../../../mapping.hpp"

#include "../../util/i_chat_component.hpp"

namespace sdk
{
	class gui_new_chat final : public vmhook::object<sdk::gui_new_chat>
	{
	public:
		explicit gui_new_chat(const vmhook::oop_type_t instance) noexcept
			: vmhook::object<sdk::gui_new_chat>{ instance }
		{

		}

		auto print_chat_message(const std::unique_ptr<sdk::i_chat_component>& chat_component) const noexcept
			-> void
		{
			get_method(mapping::gui_new_chat::printChatMessage)->call(chat_component);
		}
	};
}
