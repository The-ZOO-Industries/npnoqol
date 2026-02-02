#pragma once

#include "../../Module/Module.hpp"

class ChatManager final : public Module
{
public:
    ChatManager();

    ~ChatManager() override;

    auto Update() -> void override;
    auto ClearCache() -> void override {};

private:
    std::vector<std::regex> blacklistedLines;
};