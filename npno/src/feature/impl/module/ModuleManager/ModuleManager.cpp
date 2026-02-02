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
	this->RegisterModule<AutoGG>();
	this->RegisterModule<ChatManager>();
	this->RegisterModule<GamemodeManager>();
	this->RegisterModule<NickManager>();
	this->RegisterModule<ScoreboardManager>();

	this->RegisterModule<BlitzSurvivalGames>();

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
			hypixelModule->SetEnable(Hypixel::ToString(hypixelModule->GetGamemode()) == GamemodeManager::GetCurrentGamemode());

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