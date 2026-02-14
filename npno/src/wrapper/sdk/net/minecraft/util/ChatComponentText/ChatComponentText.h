#pragma once

#include "../../src/wrapper/sdk/net/minecraft/util/IChatComponent/IChatComponent.h"

class ChatComponentText final : public IChatComponent
{
public:
    explicit ChatComponentText(maps::ChatComponentText instance);
    explicit ChatComponentText(const std::string& text);

    virtual ~ChatComponentText() override;
};