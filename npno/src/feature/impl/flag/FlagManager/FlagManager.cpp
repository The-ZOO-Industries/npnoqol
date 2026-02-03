#include "FlagManager.hpp"

FlagManager::FlagManager()
{

}

FlagManager::~FlagManager() = default;

auto FlagManager::Update() const -> void
{    
	bool getPlayers{ false };
	for (const std::unique_ptr<Flag>& flag : this->flags)
	{   
		if (flag->SanityCheck())
		{
			if (!getPlayers)
			{
				Flag::UpdatePlayers();
				getPlayers = true;
			}

			flag->Update();
		}
		else
		{
			flag->ClearCache();
		}
	}
}

template<typename F>
auto FlagManager::RegisterFlag() -> void
{
	this->flags.emplace_back(std::make_unique<F>());
}