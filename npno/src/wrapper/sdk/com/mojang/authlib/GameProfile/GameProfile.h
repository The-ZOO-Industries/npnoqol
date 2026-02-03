#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/com/mojang/authlib/properties/PropertyMap/PropertyMap.h"

class GameProfile final : public JavaClass
{
public:
	explicit GameProfile(const jobject instance);

	virtual ~GameProfile() override;

	[[nodiscard]] std::string GetName() const;

	[[nodiscard]] std::unique_ptr<PropertyMap> GetProperties() const;
};

namespace maps
{
	BEGIN_KLASS_DEF(GameProfile, "com/mojang/authlib/GameProfile")
        jni::method<String, "getName"> getName{ *this };
        jni::method<PropertyMap, "getProperties"> getProperties{ *this };
    END_KLASS_DEF()
}