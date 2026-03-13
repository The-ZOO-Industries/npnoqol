#pragma once

#include <easy_jni/easy_jni.hpp>

namespace jni
{
	class entity : public jni::object
	{
	public:
		explicit entity(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto get_unique_id() const
			-> std::unique_ptr<jni::uuid>
		{
			return get_method<jni::uuid>("getUniqueID")->call();
		}

		auto is_dead() const
			-> bool
		{
			return get_field<bool>("isDead")->get();
		}
	};
}