#pragma once

#include "../../Command/Command.hpp"

class SetHypixelAPIKey final : public Command
{
public:
	SetHypixelAPIKey();

	~SetHypixelAPIKey() override;

	auto OnCommand(const std::vector<std::string>& args) -> void override;
};