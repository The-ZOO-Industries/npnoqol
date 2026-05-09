#pragma once

#include "../../../../mapping.hpp"

#include "gui_new_chat.hpp"

namespace sdk
{
	class gui_ingame final : public vmhook::object<sdk::gui_ingame>
	{
	public:
		explicit gui_ingame(const vmhook::oop_type_t instance) noexcept
			: vmhook::object<sdk::gui_ingame>{ instance }
		{

		}

		auto get_chat_gui() const noexcept
			-> std::unique_ptr<sdk::gui_new_chat>
		{
			return get_field(mapping::gui_ingame::persistantChatGUI)->get();
		}
	};
}
