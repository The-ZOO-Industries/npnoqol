#pragma once

#include "../../HypixelModule/HypixelModule.hpp"

class GamemodeManager final : public HypixelModule
{
public:
    GamemodeManager();

    ~GamemodeManager() override;

    auto Update() -> void override;

    static auto GetCurrentGamemode() -> std::string;
    static auto GetCurrentMode() -> std::string;

private:
    auto ExtractJson(const std::string& line) -> std::string;

    inline static std::string currentGamemode{};
    inline static std::string currentMode{};
};