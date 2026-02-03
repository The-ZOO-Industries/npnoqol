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

namespace maps
{
	BEGIN_KLASS_DEF(Collection, "java/util/Collection")
        jni::method<jint, "size"> size{ *this };
        jni::method<jni::array<Object>, "toArray"> toArray{ *this };
    END_KLASS_DEF()
}