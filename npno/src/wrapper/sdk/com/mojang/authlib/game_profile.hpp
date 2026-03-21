#pragma once

#include <easy_jni/easy_jni.hpp>

namespace jni
{
	class game_profile final : public jni::object
	{
	public:
		explicit game_profile(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto get_name() const
			-> std::string
		{
			return get_method<std::string>(mapping::game_profile::getName)->call();
		}
	};
}