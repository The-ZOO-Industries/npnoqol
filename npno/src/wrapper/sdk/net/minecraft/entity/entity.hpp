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
	};
}