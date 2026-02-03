#include "Entity.h"

Entity::Entity(const jobject instance)
	: JavaClass(instance)
{

}

Entity::~Entity() = default;

bool Entity::IsSprinting() const
{
	return static_cast<bool>(maps::Entity(this->instance).isSprinting.call());
}

bool Entity::IsSneaking() const
{
	return static_cast<bool>(maps::Entity(this->instance).isSneaking.call());
}

bool Entity::IsInvisible() const
{
	return static_cast<bool>(maps::Entity(this->instance).isInvisible.call());
}

bool Entity::IsEating() const
{
	return static_cast<bool>(maps::Entity(this->instance).isEating.call());
}

bool Entity::IsRiding() const
{
	return static_cast<bool>(maps::Entity(this->instance).isRiding.call());
}

bool Entity::IsOnGround() const
{
	return static_cast<bool>(maps::Entity(this->instance).onGround.get());
}

float Entity::GetRotationYaw() const
{
	return static_cast<float>(maps::Entity(this->instance).rotationYaw.get());
}

float Entity::GetRotationPitch() const
{
	return static_cast<float>(maps::Entity(this->instance).rotationPitch.get());
}

float Entity::GetLastRotationYaw() const
{
	return static_cast<float>(maps::Entity(this->instance).prevRotationYaw.get());
}

float Entity::GetLastRotationPitch() const
{
	return static_cast<float>(maps::Entity(this->instance).prevRotationPitch.get());
}

std::unique_ptr<UUID_J> Entity::GetUniqueID() const
{
	jni::frame f;

	return std::make_unique<UUID_J>(jni::make_global(maps::Entity(this->instance).getUniqueID.call()));
}

std::string Entity::GetName() const
{
	jni::frame f;

	return JavaUtil::JStringToString(static_cast<jstring>(maps::Entity(this->instance).getName.call()));
}

void Entity::AddChatMessage(const std::unique_ptr<IChatComponent>& chatComponent) const
{
	jni::frame f;

	maps::IChatComponent chatParam(chatComponent->GetInstance());
	maps::Entity(this->instance).addChatMessage.call(chatParam);
}

double Entity::GetPosX() const
{
	return static_cast<double>(maps::Entity(this->instance).posX.get());
}

double Entity::GetPosY() const
{
	return static_cast<double>(maps::Entity(this->instance).posY.get());
}

double Entity::GetPosZ() const
{
	return static_cast<double>(maps::Entity(this->instance).posZ.get());
}

double Entity::GetLastTickPosX() const
{
	return static_cast<double>(maps::Entity(this->instance).lastTickPosX.get());
}

double Entity::GetLastTickPosY() const
{
	return static_cast<double>(maps::Entity(this->instance).lastTickPosY.get());
}

double Entity::GetLastTickPosZ() const
{
	return static_cast<double>(maps::Entity(this->instance).lastTickPosZ.get());
}

double Entity::GetMotionX() const
{
	return static_cast<double>(maps::Entity(this->instance).motionX.get());
}

double Entity::GetMotionY() const
{
	return static_cast<double>(maps::Entity(this->instance).motionY.get());
}

double Entity::GetMotionZ() const
{
	return static_cast<double>(maps::Entity(this->instance).motionZ.get());
}