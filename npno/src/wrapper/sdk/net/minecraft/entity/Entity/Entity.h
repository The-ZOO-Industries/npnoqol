#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/java/util/UUID/UUID.h"
#include "../../src/wrapper/sdk/net/minecraft/util/ChatComponentText/ChatComponentText.h"

class Entity : public JavaClass
{
public:
	explicit Entity(const jobject instance);

	virtual ~Entity() override;

	[[nodiscard]] virtual bool IsSprinting() const final;
	[[nodiscard]] virtual bool IsSneaking() const final;
	[[nodiscard]] virtual bool IsInvisible() const final;
	[[nodiscard]] virtual bool IsOnGround() const final;
	[[nodiscard]] virtual bool IsEating() const final;
	[[nodiscard]] virtual bool IsRiding() const final;

	[[nodiscard]] virtual float GetRotationYaw() const final;
	[[nodiscard]] virtual float GetRotationPitch() const final;
	[[nodiscard]] virtual float GetLastRotationYaw() const final;
	[[nodiscard]] virtual float GetLastRotationPitch() const final;

	[[nodiscard]] virtual double GetPosX() const final;
	[[nodiscard]] virtual double GetPosY() const final;
	[[nodiscard]] virtual double GetPosZ() const final;
	[[nodiscard]] virtual double GetLastTickPosX() const final;
	[[nodiscard]] virtual double GetLastTickPosY() const final;
	[[nodiscard]] virtual double GetLastTickPosZ() const final;
	[[nodiscard]] virtual double GetMotionX() const final;
	[[nodiscard]] virtual double GetMotionY() const final;
	[[nodiscard]] virtual double GetMotionZ() const final;

	[[nodiscard]] virtual std::unique_ptr<UUID_J> GetUniqueID() const final;

	[[nodiscard]] virtual std::string GetName() const final;

	virtual void AddChatMessage(const std::unique_ptr<IChatComponent>& chatComponent) const final;
};