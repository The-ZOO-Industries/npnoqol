#pragma once

#include "../command.hpp"

namespace zoo
{
	class find_nick final : public zoo::command
	{
	public:
		find_nick() noexcept;

		~find_nick() noexcept;

		auto on_command(const std::vector<std::string>& args) const noexcept
			-> void override;
	};
}
