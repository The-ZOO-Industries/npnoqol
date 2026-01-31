#include "FeatureManager.hpp"

FeatureManager::FeatureManager()
	: commandManager{ std::make_unique<CommandManager>() }
	, flagManager{ std::make_unique<FlagManager>() }
	, moduleManager{ std::make_unique<ModuleManager>() }
{

}

FeatureManager::~FeatureManager() = default;

auto FeatureManager::Update() const -> void
{
	this->commandManager->Update();
	this->flagManager->Update();
	this->moduleManager->Update();
}