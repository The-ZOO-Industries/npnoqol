#pragma once

#include "../../HypixelModule/HypixelModule.hpp"

class AutoGG final : public HypixelModule
{
public:
    AutoGG();

    ~AutoGG() override;

    auto Update() -> void override;

private:
    auto RandomCase(const std::string& message) const -> std::string;

    std::vector<std::regex> autoGGLines;
};