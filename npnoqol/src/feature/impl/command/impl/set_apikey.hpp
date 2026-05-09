#pragma once

#include "../command.hpp"

namespace zoo
{
	class set_apikey final : public zoo::command
	{
	public:
		set_apikey() noexcept;

		~set_apikey() noexcept;

		virtual auto on_command(const std::vector<std::string>& args) const noexcept
			-> void override;
	};
}