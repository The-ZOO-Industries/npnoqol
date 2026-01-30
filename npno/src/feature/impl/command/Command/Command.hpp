#pragma once

#include "../../../Feature/Feature.hpp"

class Command : public Feature
{
public:
	Command(const std::string& name = "", const std::string& usage = "");

	virtual ~Command();

	virtual auto Update() -> void override final;

protected:
	std::string ExtractBetweenQuotes(const std::string& text);
	std::vector<std::string> GetArguments(const std::string& string);

	std::string name;
	std::string usage;
};