#pragma once

#include "../feature/FeatureManager/FeatureManager.hpp"

class Base final
{
public:
    Base();

    ~Base();

    auto Run() -> void;

private:
    std::unique_ptr<FeatureManager> featureManager;

    bool running;
};