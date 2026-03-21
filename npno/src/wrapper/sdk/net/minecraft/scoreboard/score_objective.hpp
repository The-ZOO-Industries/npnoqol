#pragma once

#include <easy_jni/easy_jni.hpp>

#include "score_dummy_criteria.hpp"

namespace jni
{
	class score_objective final : public jni::object
	{
	public:
		explicit score_objective(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto set_name(const std::string& value) const
			-> void
		{
			get_field<std::string>(mapping::score_objective::name)->set(value);
		}

		auto get_name() const
			-> std::string
		{
			return get_field<std::string>(mapping::score_objective::name)->get();
		}

		auto get_display_name() const
			-> std::string
		{
			return get_field<std::string>(mapping::score_objective::displayName)->get();
		}

		auto set_display_name(const std::string& value) const
			-> void
		{
			get_field<std::string>(mapping::score_objective::displayName)->set(value);
		}
	};
}