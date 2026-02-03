#include "Minecraft.h"

Minecraft::Minecraft()
    : JavaClass(nullptr)
{
    jni::frame f;

    maps::Minecraft mc{};
    this->instance = Jvm::env->NewGlobalRef(jobject(mc.theMinecraft.get()));
}

Minecraft::~Minecraft() = default;

auto Minecraft::GetThePlayer() const -> std::unique_ptr<EntityPlayerSP>
{
    jni::frame f;

    return std::make_unique<EntityPlayerSP>(jobject(maps::EntityPlayerSP(maps::Minecraft(this->instance).thePlayer.get(), true)));
}

auto Minecraft::GetTheWorld() const -> std::unique_ptr<WorldClient>
{
    jni::frame f;

    return std::make_unique<WorldClient>(jobject(maps::WorldClient(maps::Minecraft(this->instance).theWorld.get(), true)));
}

auto Minecraft::GetIngameGUI() const -> std::unique_ptr<GuiIngame>
{
    jni::frame f;

    return std::make_unique<GuiIngame>(jobject(maps::GuiIngame(maps::Minecraft(this->instance).ingameGUI.get(), true)));
}