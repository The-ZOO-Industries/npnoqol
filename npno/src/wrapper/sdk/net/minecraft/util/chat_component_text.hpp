#pragma once

#include "i_chat_component.hpp"

namespace jni
{
	class chat_component_text final : public jni::i_chat_component
	{
	public:
		explicit chat_component_text(const jobject instance)
			: jni::i_chat_component{ instance }
		{

		}
	};
}