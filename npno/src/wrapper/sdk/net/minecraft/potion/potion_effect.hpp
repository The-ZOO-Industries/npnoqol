#pragma once

#include <easy_jni/easy_jni.hpp>

namespace jni
{
	class potion_effect final : public jni::object
	{
	public:
		explicit potion_effect(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto get_duration() const
			-> int
		{
			return get_method<int>("getDuration")->call();
		}

		auto get_effect_name() const
			-> std::string
		{
			return get_method<std::string>("getEffectName")->call();
		}
	};
}