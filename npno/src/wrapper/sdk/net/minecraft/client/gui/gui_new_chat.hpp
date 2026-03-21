#pragma once

#include <easy_jni/easy_jni.hpp>

#include "../../util/i_chat_component.hpp"

namespace jni
{
	class gui_new_chat final : public jni::object
	{
	public:
		explicit gui_new_chat(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto print_chat_message(const std::unique_ptr<jni::i_chat_component>& value)
			-> void
		{
			get_method<void, jni::i_chat_component>(mapping::gui_new_chat::printChatMessage)->call(value);
		}
	};
}