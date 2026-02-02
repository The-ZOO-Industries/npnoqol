#pragma once

#include "../../Module/Module.hpp"

class AutoGG final : public Module
{
public:
    AutoGG();

    ~AutoGG() override;

    auto Update() -> void override;
    auto ClearCache() -> void override {};

private:
    auto RandomCase(const std::string& message) const -> std::string;

    std::vector<std::regex> autoGGLines;
};