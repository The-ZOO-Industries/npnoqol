#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

class Collection : public JavaClass
{
public:
	explicit Collection(maps::Collection instance);

	virtual ~Collection() override;

	[[nodiscard]] jint Size() const;
	[[nodiscard]] jni::array<maps::Object> ToArray() const;
};