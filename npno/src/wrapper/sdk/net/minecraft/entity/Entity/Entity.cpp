#include "Entity.h"

Entity::Entity(maps::Entity instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

Entity::~Entity() = default;

bool Entity::IsSprinting() const
{
    return static_cast<bool>(maps::Entity(this->instance.object_instance).isSprinting.call());
}

bool Entity::IsSneaking() const
{
    return static_cast<bool>(maps::Entity(this->instance.object_instance).isSneaking.call());
}

bool Entity::IsInvisible() const
{
    return static_cast<bool>(maps::Entity(this->instance.object_instance).isInvisible.call());
}

bool Entity::IsEating() const
{
    return static_cast<bool>(maps::Entity(this->instance.object_instance).isEating.call());
}

bool Entity::IsRiding() const
{
    return static_cast<bool>(maps::Entity(this->instance.object_instance).isRiding.call());
}

bool Entity::IsOnGround() const
{
    return static_cast<bool>(maps::Entity(this->instance.object_instance).onGround.get());
}

float Entity::GetRotationYaw() const
{
    return static_cast<float>(maps::Entity(this->instance.object_instance).rotationYaw.get());
}

float Entity::GetRotationPitch() const
{
    return static_cast<float>(maps::Entity(this->instance.object_instance).rotationPitch.get());
}

float Entity::GetLastRotationYaw() const
{
    return static_cast<float>(maps::Entity(this->instance.object_instance).prevRotationYaw.get());
}

float Entity::GetLastRotationPitch() const
{
    return static_cast<float>(maps::Entity(this->instance.object_instance).prevRotationPitch.get());
}

std::unique_ptr<UUID_J> Entity::GetUniqueID() const
{
    maps::UUID uuid = maps::Entity(this->instance.object_instance).getUniqueID.call();
    maps::UUID globalUUID{ uuid.object_instance, true };
    return std::make_unique<UUID_J>(globalUUID);
}

std::string Entity::GetName() const
{
    maps::String name = maps::Entity(this->instance.object_instance).getName.call();
    return JavaUtil::JStringToString((jstring)jobject(name));
}

void Entity::AddChatMessage(const std::unique_ptr<IChatComponent>& chatComponent) const
{
    maps::IChatComponent chatParam{ chatComponent->GetInstance().object_instance };
    maps::Entity(this->instance.object_instance).addChatMessage.call(chatParam);
}

double Entity::GetPosX() const
{
    return static_cast<double>(maps::Entity(this->instance.object_instance).posX.get());
}

double Entity::GetPosY() const
{
    return static_cast<double>(maps::Entity(this->instance.object_instance).posY.get());
}

double Entity::GetPosZ() const
{
    return static_cast<double>(maps::Entity(this->instance.object_instance).posZ.get());
}

double Entity::GetLastTickPosX() const
{
    return static_cast<double>(maps::Entity(this->instance.object_instance).lastTickPosX.get());
}

double Entity::GetLastTickPosY() const
{
    return static_cast<double>(maps::Entity(this->instance.object_instance).lastTickPosY.get());
}

double Entity::GetLastTickPosZ() const
{
    return static_cast<double>(maps::Entity(this->instance.object_instance).lastTickPosZ.get());
}

double Entity::GetMotionX() const
{
    return static_cast<double>(maps::Entity(this->instance.object_instance).motionX.get());
}

double Entity::GetMotionY() const
{
    return static_cast<double>(maps::Entity(this->instance.object_instance).motionY.get());
}

double Entity::GetMotionZ() const
{
    return static_cast<double>(maps::Entity(this->instance.object_instance).motionZ.get());
}