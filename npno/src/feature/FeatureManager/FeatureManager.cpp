#include "FeatureManager.hpp"

FeatureManager::FeatureManager()
	: flag{ std::make_unique<Flag>() }
	, command{ std::make_unique<Command>() }
	module{ std::make_unique<Module>() }
{
}