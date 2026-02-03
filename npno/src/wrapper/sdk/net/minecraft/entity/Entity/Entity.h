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

namespace maps
{
    BEGIN_KLASS_DEF(Entity, "net/minecraft/entity/Entity")
        jni::method<jboolean, "isSprinting"> isSprinting{ *this };
        jni::method<jboolean, "isSneaking"> isSneaking{ *this };
        jni::method<jboolean, "isInvisible"> isInvisible{ *this };
        jni::method<jboolean, "isEating"> isEating{ *this };
        jni::method<jboolean, "isRiding"> isRiding{ *this };
        jni::method<UUID, "getUniqueID"> getUniqueID{ *this };
        jni::method<String, "getName"> getName{ *this };
        jni::method<void, "addChatMessage", jni::NOT_STATIC, IChatComponent> addChatMessage{ *this };

        jni::field<jboolean, "onGround"> onGround{ *this };
        jni::field<jfloat, "rotationYaw"> rotationYaw{ *this };
        jni::field<jfloat, "rotationPitch"> rotationPitch{ *this };
        jni::field<jfloat, "prevRotationYaw"> prevRotationYaw{ *this };
        jni::field<jfloat, "prevRotationPitch"> prevRotationPitch{ *this };
        jni::field<jdouble, "posX"> posX{ *this };
        jni::field<jdouble, "posY"> posY{ *this };
        jni::field<jdouble, "posZ"> posZ{ *this };
        jni::field<jdouble, "lastTickPosX"> lastTickPosX{ *this };
        jni::field<jdouble, "lastTickPosY"> lastTickPosY{ *this };
        jni::field<jdouble, "lastTickPosZ"> lastTickPosZ{ *this };
        jni::field<jdouble, "motionX"> motionX{ *this };
        jni::field<jdouble, "motionY"> motionY{ *this };
        jni::field<jdouble, "motionZ"> motionZ{ *this };
    END_KLASS_DEF()
}