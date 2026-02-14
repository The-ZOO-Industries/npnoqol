#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/net/minecraft/client/network/NetworkPlayerInfo/NetworkPlayerInfo.h"
#include "../../src/wrapper/sdk/java/util/List/List.h"

class NetHandlerPlayClient final : public JavaClass
{
public:
    explicit NetHandlerPlayClient(maps::NetHandlerPlayClient instance);

    virtual ~NetHandlerPlayClient() override;

    [[nodiscard]] std::vector<std::unique_ptr<NetworkPlayerInfo>> GetPlayerInfoMap() const;
};