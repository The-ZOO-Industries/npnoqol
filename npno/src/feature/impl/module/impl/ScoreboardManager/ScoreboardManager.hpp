#pragma once

#include "../../Module/Module.hpp"

class ScoreboardManager final : public Module
{
public:
    ScoreboardManager();

    ~ScoreboardManager() override;

    auto Update() -> void override;
    auto ClearCache() -> void override {};
};