#pragma once

#include "i_chat_component.hpp"

namespace sdk
{
	class chat_component_text final : public sdk::i_chat_component
	{
	public:
		explicit chat_component_text(const vmhook::oop_type_t instance) noexcept
			: sdk::i_chat_component{ instance }
		{

		}

		auto construct(const std::string& text) const noexcept
			-> void
		{
			get_method("<init>")->call(text);
		}
	};
}