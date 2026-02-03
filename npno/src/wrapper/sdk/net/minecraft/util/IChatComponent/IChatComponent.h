#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

class IChatComponent : public JavaClass
{
public:
    explicit IChatComponent(const jobject instance);

    virtual ~IChatComponent() override;

    [[nodiscard]] std::string GetFormattedText() const;
    [[nodiscard]] std::string GetUnformattedText() const;
};