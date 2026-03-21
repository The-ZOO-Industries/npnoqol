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
			return get_method<std::string>(mapping::score_player_team::getTeamName)->call();
		}

		auto get_membership_collection() const
			-> std::vector<std::string>
		{
			return get_method<jni::collection>(mapping::score_player_team::getMembershipCollection)->call()->to_vector<std::string>();
		}

		auto get_name_prefix() const
			-> std::string
		{
			return get_method<std::string>(mapping::score_player_team::getColorPrefix)->call();
		}

		auto get_name_suffix() const
			-> std::string
		{
			return get_method<std::string>(mapping::score_player_team::getColorSuffix)->call();
		}

		auto set_name_prefix(const std::string& value) const
			-> void
		{
			get_method<void, std::string>(mapping::score_player_team::setNamePrefix)->call(value);
		}

		auto set_name_suffix(const std::string& value) const
			-> void
		{
			get_method<void, std::string>(mapping::score_player_team::setNameSuffix)->call(value);
		}
	};
}