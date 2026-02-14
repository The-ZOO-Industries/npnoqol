#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/net/minecraft/client/gui/ChatLine/ChatLine.h"
#include "../../src/wrapper/sdk/java/util/List/List.h"

class GuiNewChat final : public JavaClass
{
public:
    explicit GuiNewChat(maps::GuiNewChat instance);

    virtual ~GuiNewChat() override;

    [[nodiscard]] std::vector<std::unique_ptr<ChatLine>> GetChatLines() const;

    void RefreshChat() const;
    void DeleteChatLine(const I32 id) const;
};