#pragma once

#include <easy_jni/easy_jni.hpp>

namespace jni
{
	class score_player_team final : public jni::object
	{
	public:
		explicit score_player_team(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto get_team_name() const
			-> std::string
		{
			return get_method<std::string>("getTeamName")->call();
		}

		auto get_membership_collection() const
			-> std::vector<std::string>
		{
			return get_method<jni::collection>("getMembershipCollection")->call()->to_vector<std::string>();
		}

		auto get_name_prefix() const
			-> std::string
		{
			return get_method<std::string>("getColorPrefix")->call();
		}

		auto get_name_suffix() const
			-> std::string
		{
			return get_method<std::string>("getColorSuffix")->call();
		}

		auto set_name_prefix(const std::string& value) const
			-> void
		{
			get_method<void, std::string>("setNamePrefix")->call(value);
		}

		auto set_name_suffix(const std::string& value) const
			-> void
		{
			get_method<void, std::string>("setNameSuffix")->call(value);
		}
	};
}