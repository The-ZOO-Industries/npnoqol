#include "CommandManager.hpp"

#include "../impl?SetHypixelAPIKey/SetHypixelAPIKey.hpp"

CommandManager::CommandManager()
{
	this->RegisterCommand<SetHypixelAPIKey>();9
}

CommandManager::~CommandManager() = default;

auto CommandManager::Update() const -> void
{
	for (const std::unique_ptr<Command>& command : this->commands)
	{
		command->Update();
	}
}

template<typename C>
auto CommandManager::RegisterCommand() -> void
{
	this->commands.emplace_back(std::make_unique<C>());
}