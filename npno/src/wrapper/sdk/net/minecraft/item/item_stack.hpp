#pragma once

#include <easy_jni/easy_jni.hpp>

namespace jni
{
	class item_stack final : public jni::object
	{
	public:
		explicit item_stack(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto get_display_name() const
			-> std::string
		{
			return get_method<std::string>("getDisplayName")->call();
		}
	};
}