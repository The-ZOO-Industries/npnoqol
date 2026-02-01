#pragma once

#include "../../HypixelModule/HypixelModule.hpp"

class ChatManager final : public HypixelModule
{
public:
    ChatManager();

    ~ChatManager() override;

    auto Update() -> void override;

private:
    std::vector<std::regex> blacklistedLines;
};