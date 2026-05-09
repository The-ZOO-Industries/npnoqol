#pragma once

#include "../../../mapping.hpp"

namespace sdk
{
	class i_chat_component : public vmhook::object<sdk::i_chat_component>
	{
	public:
		explicit i_chat_component(const vmhook::oop_type_t instance) noexcept
			: vmhook::object<sdk::i_chat_component>{ instance }
		{

		}

		auto get_formatted_text() const noexcept
			-> std::string
		{
			return get_method(mapping::i_chat_component::getFormattedText)->call();
		}

		auto get_unformatted_text() const noexcept
			-> std::string
		{
			return get_method(mapping::i_chat_component::getUnformattedText)->call();
		}
	};
}