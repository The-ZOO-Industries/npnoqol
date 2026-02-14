#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/com/mojang/authlib/GameProfile/GameProfile.h"
#include "../../src/wrapper/sdk/net/minecraft/util/IChatComponent/IChatComponent.h"

class NetworkPlayerInfo final : public JavaClass
{
public:
    explicit NetworkPlayerInfo(maps::NetworkPlayerInfo instance);

    virtual ~NetworkPlayerInfo() override;

    [[nodiscard]] std::unique_ptr<GameProfile> GetGameProfile() const;
    [[nodiscard]] std::unique_ptr<IChatComponent> GetDisplayName() const;

    void SetDisplayName(const std::unique_ptr<IChatComponent>& newName);
};