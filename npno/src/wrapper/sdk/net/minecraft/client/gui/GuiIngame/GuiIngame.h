#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/net/minecraft/client/gui/GuiNewChat/GuiNewChat.h"
#include "../../src/wrapper/sdk/net/minecraft/client/gui/GuiPlayerTabOverlay/GuiPlayerTabOverlay.h"

class GuiIngame final : public JavaClass
{
public:
    explicit GuiIngame(maps::GuiIngame instance);

    virtual ~GuiIngame() override;

    [[nodiscard]] std::unique_ptr<GuiNewChat> GetPersistantChatGUI() const;
    [[nodiscard]] std::unique_ptr<GuiPlayerTabOverlay> GetOverlayPlayerList() const;
};