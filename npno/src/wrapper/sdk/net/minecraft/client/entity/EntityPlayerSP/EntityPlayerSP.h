#pragma once

#include "../../src/wrapper/sdk/net/minecraft/entity/player/EntityPlayer/EntityPlayer.h"

#include "../../src/wrapper/sdk/net/minecraft/client/network/NetHandlerPlayClient/NetHandlerPlayClient.h"

class EntityPlayerSP final : public EntityPlayer
{
public:
	explicit EntityPlayerSP(const jobject instance);

	virtual ~EntityPlayerSP() override;

	[[nodiscard]] std::unique_ptr<NetHandlerPlayClient> GetSendQueue() const;

	void SendChatMessage(const std::string& message) const;
};