#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/net/minecraft/client/network/NetworkPlayerInfo/NetworkPlayerInfo.h"

class NetHandlerPlayClient final : public JavaClass
{
public:
	explicit NetHandlerPlayClient(const jobject instance);

	virtual ~NetHandlerPlayClient() override;

	[[nodiscard]] std::vector<std::unique_ptr<NetworkPlayerInfo>> GetPlayerInfoMap() const;
};

namespace maps
{
    BEGIN_KLASS_DEF(NetHandlerPlayClient, "net/minecraft/client/network/NetHandlerPlayClient")
        jni::method<Collection, "getPlayerInfoMap"> getPlayerInfoMap{ *this };
    END_KLASS_DEF()
}