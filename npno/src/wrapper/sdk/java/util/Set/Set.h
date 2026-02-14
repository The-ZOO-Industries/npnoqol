#pragma once

#include "../../src/wrapper/sdk/java/util/Collection/Collection.h"

class Set final : public Collection
{
public:
    explicit Set(maps::Set instance);

    virtual ~Set() override;
};