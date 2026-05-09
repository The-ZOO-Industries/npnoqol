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
			if (!vmhook::detail::find_call_stub_entry())
			{
				vmhook::hotspot::klass* const klass{ vmhook::find_class(mapping::chat_component_text::clazz) };
				void* const string_oop{ vmhook::make_java_string(text) };
				if (!klass || !string_oop)
				{
					return;
				}

				for (const char* const field_name : { "text", "field_150267_b", "b", "a" })
				{
					if (vmhook::find_field(klass, field_name))
					{
						vmhook::set_field(this->get_instance(), klass, field_name, vmhook::hotspot::encode_oop_pointer(string_oop));
						return;
					}
				}
			}

			get_method("<init>")->call(text);
		}
	};
}
