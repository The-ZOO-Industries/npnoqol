#pragma once

#include "../../src/wrapper/sdk/java/util/Collection/Collection.h"

class List final : public Collection
{
public:
    explicit List(maps::List instance);

    virtual ~List() override;

    [[nodiscard]] maps::Object Get(const jint index) const;
};