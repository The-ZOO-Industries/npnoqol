#pragma once

#include <easy_jni/easy_jni.hpp>

#include "gui_new_chat.hpp"

namespace jni
{
	class gui_ingame final : public jni::object
	{
	public:
		explicit gui_ingame(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto get_persistant_chat_gui() const
			-> std::unique_ptr<jni::gui_new_chat>
		{
			return get_field<jni::gui_new_chat>(mapping::gui_ingame::persistantChatGUI)->get();
		}
	};
}