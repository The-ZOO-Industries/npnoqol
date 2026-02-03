#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/com/mojang/authlib/GameProfile/GameProfile.h"
#include "../../src/wrapper/sdk/net/minecraft/util/IChatComponent/IChatComponent.h"

class NetworkPlayerInfo final : public JavaClass
{
public:
	explicit NetworkPlayerInfo(const jobject instance);

	virtual ~NetworkPlayerInfo() override;

	[[nodiscard]] std::unique_ptr<GameProfile> GetGameProfile() const;
	[[nodiscard]] std::unique_ptr<IChatComponent> GetDisplayName() const;

	void SetDisplayName(const std::unique_ptr<IChatComponent>& newName);
};

namespace maps
{
    BEGIN_KLASS_DEF(NetworkPlayerInfo, "net/minecraft/client/network/NetworkPlayerInfo")
        jni::method<GameProfile, "getGameProfile"> getGameProfile{ *this };
        jni::method<IChatComponent, "getDisplayName"> getDisplayName{ *this };
        jni::method<void, "setDisplayName", jni::NOT_STATIC, IChatComponent> setDisplayName{ *this };
    END_KLASS_DEF()
}