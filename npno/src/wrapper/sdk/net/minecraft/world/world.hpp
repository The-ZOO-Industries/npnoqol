#pragma once

#include <easy_jni/easy_jni.hpp>

namespace jni
{
	class world : public jni::object
	{
	public:
		explicit world(const jobject instance)
			: jni::object{ instance }
		{

		}
	};
}