#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/net/minecraft/client/entity/EntityPlayerSP/EntityPlayerSP.h"
#include "../../src/wrapper/sdk/net/minecraft/client/multiplayer/WorldClient/WorldClient.h"
#include "../../src/wrapper/sdk/net/minecraft/client/gui/GuiIngame/GuiIngame.h"

class Minecraft final : public JavaClass
{
public:
    Minecraft();

    virtual ~Minecraft() override;

    [[nodiscard]] std::unique_ptr<EntityPlayerSP> GetThePlayer() const;
    [[nodiscard]] std::unique_ptr<WorldClient> GetTheWorld() const;
    [[nodiscard]] std::unique_ptr<GuiIngame> GetIngameGUI() const;
};