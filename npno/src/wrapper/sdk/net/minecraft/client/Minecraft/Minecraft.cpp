#include "Minecraft.h"

Minecraft::Minecraft()
    : JavaClass(nullptr)
{
    jni::frame f;

    maps::Minecraft mc;
    this->instance = Jvm::env->NewGlobalRef(static_cast<jobject>(mc.theMinecraft.get()));
}

Minecraft::~Minecraft() = default;

std::unique_ptr<EntityPlayerSP> Minecraft::GetThePlayer() const
{
    jni::frame f;

    return std::make_unique<EntityPlayerSP>(jni::make_global(maps::Minecraft(this->instance).thePlayer.get()));
}

std::unique_ptr<WorldClient> Minecraft::GetTheWorld() const
{
    jni::frame f;

    return std::make_unique<WorldClient>(jni::make_global(maps::Minecraft(this->instance).theWorld.get()));
}

std::unique_ptr<GuiIngame> Minecraft::GetIngameGUI() const
{
    jni::frame f;

    return std::make_unique<GuiIngame>(jni::make_global(maps::Minecraft(this->instance).ingameGUI.get()));
}