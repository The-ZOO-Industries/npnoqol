#pragma once

#include <easy_jni/easy_jni.hpp>

#include "i_score_objective_criteria.hpp"

namespace jni
{
	class score_dummy_criteria final : public jni::i_score_objective_criteria
	{
	public:
		explicit score_dummy_criteria(const jobject instance)
			: jni::i_score_objective_criteria{ instance }
		{

		}
	};
}