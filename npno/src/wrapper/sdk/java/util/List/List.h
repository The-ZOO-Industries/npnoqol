#pragma once

#include "../../src/wrapper/sdk/java/util/Collection/Collection.h"

class List final : public Collection
{
public:
	explicit List(const jobject instance);

	virtual ~List() override;

	[[nodiscard]] jobject Get(const I32 index) const;
};

namespace maps
{
	BEGIN_KLASS_DEF_EX(List, "java/util/List", Collection)
        jni::method<Object, "get", jni::NOT_STATIC, jint> get{ *this };
    END_KLASS_DEF()
}