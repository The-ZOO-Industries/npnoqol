#pragma once

#include "../Feature/Feature.hpp"

#include "../impl/command/CommandManager/CommandManager.hpp"
#include "../impl/flag/FlagManager/FlagManager.hpp"
#include "../impl/module/ModuleManager/ModuleManager.hpp"

class FeatureManager final
{
public:
	FeatureManager();

	~FeatureManager();

	auto Update() const -> void;

private:
	std::unique_ptr<CommandManager> commandManager;
	std::unique_ptr<FlagManager> flagManager;
	std::unique_ptr<ModuleManager> moduleManager;
};