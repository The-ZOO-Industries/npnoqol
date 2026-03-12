#pragma once

#include "../../feature.hpp"

namespace npno
{
	class command : public npno::feature
	{
	public:
		command(const std::string& name = "", const std::string& usage = "");

		virtual ~command();
			
		virtual auto on_command(const std::vector<std::string>& args) const 
			-> void = 0;

		virtual auto update() const
			-> void override final;

		auto on_chat_message(const std::string& message) const
			-> bool;

		auto get_arguments(const std::string& command) const
			-> std::vector<std::string>;

		auto get_name() const
			-> std::string;
			 
	protected:
		std::string name;
		std::string usage;
	};
}