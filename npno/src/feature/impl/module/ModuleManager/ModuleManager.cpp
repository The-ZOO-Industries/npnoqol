#include "ModuleManager.hpp"

#include "../HypixelModule/HypixelModule.hpp"

#include "../impl/BlitzSurvivalGames/BlitzSurvivalGames.hpp"

#include "../impl/AutoGG/AutoGG.hpp"
#include "../impl/ChatManager/ChatManager.hpp"
#include "../impl/GamemodeManager/GamemodeManager.hpp"
#include "../impl/NickManager/NickManager.hpp"
#include "../impl/ScoreboardManager/ScoreboardManager.hpp"

ModuleManager::ModuleManager()
{	
	this->RegisterModule<hypixel::AutoGG>();
	this->RegisterModule<hypixel::ChatManager>();
	this->RegisterModule<hypixel::GamemodeManager>();
	this->RegisterModule<hypixel::NickManager>();
	this->RegisterModule<hypixel::ScoreboardManager>();

	this->RegisterModule<hypixel::BlitzSurvivalGames>();

	chatUtil = std::make_unique<ChatUtil>();
}

ModuleManager::~ModuleManager() = default;

auto ModuleManager::Update() const -> void
{
	chatUtil->Update();
	
	for (const std::unique_ptr<Module>& module : this->modules)
	{
		if (auto* hypixelModule = dynamic_cast<HypixelModule*>(module.get()))
		{
			if (hypixelModule->GetGamemode() != HypixelGamemode::ALL)
			{
				hypixelModule->SetEnable(hypixelModule->GetGamemode() == GamemodeManager::GetCurrentGamemode());
			}

			if (!hypixelModule->IsEnable())
			{
				hypixelModule->ClearCache();
			}
		}
		
		if (module->IsEnable() and module->SanityCheck())
		{
			module->Update();
		}
	}
}

template<typename M>
auto ModuleManager::RegisterModule() -> void
{
	modules.emplace_back(std::make_unique<M>());
}