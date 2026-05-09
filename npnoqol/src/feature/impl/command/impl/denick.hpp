#pragma once

#include "../command.hpp"

namespace zoo
{
	class denick final : public zoo::command
	{
	public:
		denick() noexcept;

		~denick() noexcept;

		auto on_command(const std::vector<std::string>& args) const noexcept
			-> void override;
	};
}
