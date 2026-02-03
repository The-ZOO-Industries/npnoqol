#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/net/minecraft/client/network/NetworkPlayerInfo/NetworkPlayerInfo.h"

class GuiPlayerTabOverlay final : public JavaClass 
{
public:
	explicit GuiPlayerTabOverlay(const jobject instance);

	virtual ~GuiPlayerTabOverlay() override;

	[[nodiscard]] std::string GetPlayerName(const std::unique_ptr<NetworkPlayerInfo>& playerInfo) const;
};

namespace maps
{
    BEGIN_KLASS_DEF(GuiPlayerTabOverlay, "net/minecraft/client/gui/GuiPlayerTabOverlay")
        jni::method<String, "getPlayerName", jni::NOT_STATIC, NetworkPlayerInfo> getPlayerName{ *this };
    END_KLASS_DEF()
}