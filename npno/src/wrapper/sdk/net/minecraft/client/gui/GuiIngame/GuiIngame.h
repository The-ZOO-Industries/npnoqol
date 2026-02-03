#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/net/minecraft/client/gui/GuiNewChat/GuiNewChat.h"
#include "../../src/wrapper/sdk/net/minecraft/client/gui/GuiPlayerTabOverlay/GuiPlayerTabOverlay.h"

class GuiIngame final : public JavaClass
{
public:
	explicit GuiIngame(const jobject instance);

	virtual ~GuiIngame() override;

	[[nodiscard]] std::unique_ptr<GuiNewChat> GetPersistantChatGUI() const;
	[[nodiscard]] std::unique_ptr<GuiPlayerTabOverlay> GetOverlayPlayerList() const;
};

namespace maps
{
    BEGIN_KLASS_DEF(GuiIngame, "net/minecraft/client/gui/GuiIngame")
        jni::field<GuiNewChat, "persistantChatGUI"> persistantChatGUI{ *this };
        jni::field<GuiPlayerTabOverlay, "overlayPlayerList"> overlayPlayerList{ *this };
    END_KLASS_DEF()
}