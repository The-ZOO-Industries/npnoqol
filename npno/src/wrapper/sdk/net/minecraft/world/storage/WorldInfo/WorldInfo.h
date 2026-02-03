#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

class WorldInfo : public JavaClass
{
public:
	explicit WorldInfo(const jobject instance);

	virtual ~WorldInfo() override;

    [[nodiscard]] I64 GetRandomSeed() const;
    [[nodiscard]] I64 GetWorldTime() const;

    [[nodiscard]] std::string GetWorldName() const;
};

namespace maps
{
    BEGIN_KLASS_DEF(WorldInfo, "net/minecraft/world/storage/WorldInfo")
        jni::field<jlong, "randomSeed"> randomSeed{ *this };
        jni::field<jlong, "worldTime"> worldTime{ *this };
        jni::field<jstring, "worldName"> worldName{ *this };
    END_KLASS_DEF()
}