#pragma once

#include "../../src/wrapper/sdk/java/util/Collection/Collection.h"

class List final : public Collection
{
public:
	explicit List(const jobject instance);

	virtual ~List() override;

	[[nodiscard]] jobject Get(const I32 index) const;
};