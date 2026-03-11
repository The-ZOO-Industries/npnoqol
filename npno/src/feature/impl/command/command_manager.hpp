#pragma once

#include "command.hpp"

namespace npno
{
	class command_manager final
	{
	public:
		command_manager();

		~command_manager();

		auto update(const std::string& message) const
			-> bool;

	private:
		template <typename com>
			requires (std::is_base_of_v<npno::command, com>)
		auto register_command()
			-> void;

		std::vector <std::unique_ptr<npno::command>> commands;
	};
}