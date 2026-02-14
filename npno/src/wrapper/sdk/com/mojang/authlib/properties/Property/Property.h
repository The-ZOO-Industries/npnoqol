#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

class Property final : public JavaClass
{
public:
    explicit Property(maps::Property instance);

    virtual ~Property() override;

    [[nodiscard]] std::string GetValue() const;
    [[nodiscard]] std::string GetName() const;
};