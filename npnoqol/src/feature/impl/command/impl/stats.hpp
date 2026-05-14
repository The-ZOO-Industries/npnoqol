#pragma once

#include "../command.hpp"

namespace zoo
{
	class stats final : public zoo::command
	{
	public:
		stats() noexcept;

		~stats() noexcept;

		virtual auto on_command(const std::vector<std::string>& args) const noexcept
			-> void override;
	};
}