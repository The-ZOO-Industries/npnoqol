#pragma once

#include "../command.hpp"

namespace npno
{
	class requeue final : public npno::command
	{
	public:
		requeue();

		~requeue();

		virtual auto on_command(const std::vector<std::string>& args) const
			-> void override;

	private:
		struct gametype_mode_hash
		{
			auto operator()(const std::pair<hypixel_gametype::gametype, std::string>& value) const 
				-> std::size_t
			{
				const std::size_t h1{ std::hash<std::int32_t>{}(static_cast<std::int32_t>(value.first)) };
				const std::size_t h2{ std::hash<std::string>{}(value.second) };
				return h1 ^ (h2 << 1);
			}
		};

		inline static const std::unordered_map<std::pair<hypixel_gametype::gametype, std::string>, std::string, gametype_mode_hash> command_map =
		{
			{ { hypixel_gametype::gametype::BLITZSURVIVALGAMES, "solo_normal" }, "/play blitz_solo_normal" },
			{ { hypixel_gametype::gametype::BLITZSURVIVALGAMES, "teams_normal" }, "/play blitz_teams_normal" }
		};
	};
}