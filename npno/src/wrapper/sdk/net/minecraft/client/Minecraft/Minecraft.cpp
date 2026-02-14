#include "Minecraft.h"

Minecraft::Minecraft()
    : JavaClass(maps::Object(nullptr))
{
    maps::Minecraft mc{};
    maps::Minecraft theMinecraft = mc.theMinecraft.get();
    this->instance = maps::Object{ theMinecraft.object_instance, true };
}

Minecraft::~Minecraft() = default;

std::unique_ptr<EntityPlayerSP> Minecraft::GetThePlayer() const
{
    maps::Minecraft mc{ this->instance.object_instance, this->instance.is_global() };
    maps::EntityPlayerSP thePlayer = mc.thePlayer.get();
    maps::EntityPlayerSP globalPlayer{ thePlayer.object_instance, true };
    return std::make_unique<EntityPlayerSP>(globalPlayer);
}

std::unique_ptr<WorldClient> Minecraft::GetTheWorld() const
{
    maps::WorldClient theWorld = (maps::Minecraft)this->instance.object_instance.theWorld.get();
    maps::WorldClient globalWorld{ theWorld.object_instance, true };
    return std::make_unique<WorldClient>(globalWorld);
}

std::unique_ptr<GuiIngame> Minecraft::GetIngameGUI() const
{
    maps::Minecraft mc{ this->instance.object_instance, this->instance.is_global() };
    maps::GuiIngame ingameGUI = mc.ingameGUI.get();
    maps::GuiIngame globalGUI{ ingameGUI.object_instance, true };
    return std::make_unique<GuiIngame>(globalGUI);
}