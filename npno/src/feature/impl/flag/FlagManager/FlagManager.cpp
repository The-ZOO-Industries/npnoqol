#include "FlagManager.hpp"

FlagManager::FlagManager()
{

}

FlagManager::~FlagManager() = default;

auto FlagManager::Update() const -> void
{    
    for (const std::unique_ptr<Flag>& flag : this->flags)
	{   
		if (flag->SanityCheck())
		{
			flag->Update();
		}
		else
		{
			flag->ClearCache();
		}
	}

    Flag::UpdatePlayers();
}

template<typename F>
auto FlagManager::RegisterFlag() -> void
{
	this->flags.emplace_back(std::make_unique<F>());
}