#pragma once

#include <easy_jni/easy_jni.hpp>

namespace jni
{
	class score final : public jni::object
	{
	public:
		explicit score(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto get_score_points() const
			-> int
		{
			return get_field<int>(mapping::score::scorePoints)->get();
		}

		auto set_score_points(const int value) const
			-> void
		{
			get_field<int>(mapping::score::scorePoints)->set(value);
		}
	};
}