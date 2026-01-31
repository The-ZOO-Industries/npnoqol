#pragma once

#include "../../../Feature/Feature.hpp"

class Command : public Feature
{
public:
	Command(const std::string& name = "", const std::string& usage = "");

	virtual ~Command();

	virtual auto Update() -> void override final;

	virtual auto OnCommand(const std::vector<std::string>& args) -> void = 0;

protected:
	auto GetArguments(const std::string& command) const -> std::vector<std::string>;
	auto ExtractBetweenQuotes(const std::string& line) const -> std::string;

	std::string name;
	std::string usage;
};