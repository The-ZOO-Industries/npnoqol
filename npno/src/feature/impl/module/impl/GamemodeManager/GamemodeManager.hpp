#pragma once

#include "../../Module/Module.hpp"

class GamemodeManager final : public Module
{
public:
    GamemodeManager();

    ~GamemodeManager() override;

    auto Update() -> void override;
    auto ClearCache() -> void override {};

    static auto GetCurrentGamemode() -> std::string;
    static auto GetCurrentMode() -> std::string;

private:
    auto ExtractJson(const std::string& line) -> std::string;

    inline static std::string currentGamemode{};
    inline static std::string currentMode{};
};