#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

class Collection : public JavaClass
{
public:
	explicit Collection(const jobject instance);

	virtual ~Collection() override;

	[[nodiscard]] jint Size() const;
	[[nodiscard]] jobjectArray ToArray() const;
};