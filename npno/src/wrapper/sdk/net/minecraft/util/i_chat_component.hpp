#pragma once

#include <easy_jni/easy_jni.hpp>

namespace jni
{
	class i_chat_component : public jni::object
	{
	public:
		explicit i_chat_component(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto get_formatted_text() const
			-> std::string
		{
			return get_method<std::string>(mapping::i_chat_component::getFormattedText)->call();
		}

		auto get_unformatted_text() const
			-> std::string
		{
			return get_method<std::string>(mapping::i_chat_component::getUnformattedText)->call();
		}
	};
}