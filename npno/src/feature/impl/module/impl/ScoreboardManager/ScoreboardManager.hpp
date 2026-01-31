#pragma once

#include "../../HypixelModule/HypixelModule.hpp"

class ScoreboardManager final : public HypixelModule
{
public:
    ScoreboardManager();

    ~ScoreboardManager() override;

    auto Update() -> void override;
};