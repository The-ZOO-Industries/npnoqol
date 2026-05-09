#pragma once

#include "../../feature.hpp"

#include <sstream>
#include <vector>

namespace zoo
{
	class command : public zoo::feature
	{
	public:
		command(const std::string& name = "", const std::string& usage = "") noexcept;

		virtual ~command() noexcept;

		virtual auto on_command(const std::vector<std::string>& args) const noexcept
			-> void = 0;

		auto on_send_chat_message(const std::string& message) const noexcept
			-> bool;

		auto get_arguments(const std::string& command) const noexcept
			-> std::vector<std::string>;

		auto print_usage() const noexcept
			-> void;

		auto get_name() const noexcept
			-> std::string;

	protected:
		std::string name;
		std::string usage;
	};
}
