#pragma once

#include "../command.hpp"

namespace npno
{
	class set_apikey final : public npno::command
	{
	public:
		set_apikey();

		~set_apikey();

		virtual auto on_command(const std::vector<std::string>& args) const
			-> void override;
	};
}