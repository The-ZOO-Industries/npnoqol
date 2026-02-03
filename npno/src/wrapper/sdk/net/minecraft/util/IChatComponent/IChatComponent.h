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

namespace maps
{
    BEGIN_KLASS_DEF(IChatComponent, "net/minecraft/util/IChatComponent")
        jni::method<String, "getFormattedText"> getFormattedText{ *this };
        jni::method<String, "getUnformattedText"> getUnformattedText{ *this };
    END_KLASS_DEF()

}