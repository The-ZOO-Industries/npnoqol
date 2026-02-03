#include "Entity.h"

Entity::Entity(const jobject instance)
    : JavaClass(instance)
{
}

Entity::~Entity() = default;

auto Entity::IsSprinting() const -> bool
{
    return static_cast<bool>(maps::Entity(this->instance).isSprinting.call());
}

auto Entity::IsSneaking() const -> bool
{
    return static_cast<bool>(maps::Entity(this->instance).isSneaking.call());
}

auto Entity::IsInvisible() const -> bool
{
    return static_cast<bool>(maps::Entity(this->instance).isInvisible.call());
}

auto Entity::IsEating() const -> bool
{
    return static_cast<bool>(maps::Entity(this->instance).isEating.call());
}

auto Entity::IsRiding() const -> bool
{
    return static_cast<bool>(maps::Entity(this->instance).isRiding.call());
}

auto Entity::IsOnGround() const -> bool
{
    return static_cast<bool>(maps::Entity(this->instance).onGround.get());
}

auto Entity::GetRotationYaw() const -> float
{
    return static_cast<float>(maps::Entity(this->instance).rotationYaw.get());
}

auto Entity::GetRotationPitch() const -> float
{
    return static_cast<float>(maps::Entity(this->instance).rotationPitch.get());
}

auto Entity::GetLastRotationYaw() const -> float
{
    return static_cast<float>(maps::Entity(this->instance).prevRotationYaw.get());
}

auto Entity::GetLastRotationPitch() const -> float
{
    return static_cast<float>(maps::Entity(this->instance).prevRotationPitch.get());
}

auto Entity::GetUniqueID() const -> std::unique_ptr<UUID_J>
{
    jni::frame f;

    return std::make_unique<UUID_J>(jobject(maps::UUID(maps::Entity(this->instance).getUniqueID.call(), true)));
}

auto Entity::GetName() const -> std::string
{
    jni::frame f;

    return JavaUtil::JStringToString((jstring)jobject(maps::Entity(this->instance).getName.call()));
}

auto Entity::AddChatMessage(const std::unique_ptr<IChatComponent>& chatComponent) const -> void
{
    jni::frame f;

    maps::IChatComponent chatParam{ jobject(maps::IChatComponent(chatComponent->GetInstance(), true)) };
    maps::Entity(this->instance).addChatMessage.call(chatParam);
}

auto Entity::GetPosX() const -> double
{
    return static_cast<double>(maps::Entity(this->instance).posX.get());
}

auto Entity::GetPosY() const -> double
{
    return static_cast<double>(maps::Entity(this->instance).posY.get());
}

auto Entity::GetPosZ() const -> double
{
    return static_cast<double>(maps::Entity(this->instance).posZ.get());
}

auto Entity::GetLastTickPosX() const -> double
{
    return static_cast<double>(maps::Entity(this->instance).lastTickPosX.get());
}

auto Entity::GetLastTickPosY() const -> double
{
    return static_cast<double>(maps::Entity(this->instance).lastTickPosY.get());
}

auto Entity::GetLastTickPosZ() const -> double
{
    return static_cast<double>(maps::Entity(this->instance).lastTickPosZ.get());
}

auto Entity::GetMotionX() const -> double
{
    return static_cast<double>(maps::Entity(this->instance).motionX.get());
}

auto Entity::GetMotionY() const -> double
{
    return static_cast<double>(maps::Entity(this->instance).motionY.get());
}

auto Entity::GetMotionZ() const -> double
{
    return static_cast<double>(maps::Entity(this->instance).motionZ.get());
}