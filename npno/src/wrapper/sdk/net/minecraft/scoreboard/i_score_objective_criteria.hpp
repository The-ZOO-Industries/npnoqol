#pragma once

#include <easy_jni/easy_jni.hpp>

namespace jni
{
	class i_score_objective_criteria : public jni::object
	{
	public:
		explicit i_score_objective_criteria(const jobject instance)
			: jni::object{ instance }
		{

		}
	};
}