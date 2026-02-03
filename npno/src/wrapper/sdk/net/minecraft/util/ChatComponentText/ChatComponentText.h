#pragma once

#include "../../src/wrapper/sdk/net/minecraft/util/IChatComponent/IChatComponent.h"

class ChatComponentText final : public IChatComponent
{
public:
	explicit ChatComponentText(const jobject instance);
	explicit ChatComponentText(const std::string& text);

	virtual ~ChatComponentText() override;
};

namespace maps
{
	BEGIN_KLASS_DEF_EX(ChatComponentText, "net/minecraft/util/ChatComponentText", IChatComponent)
        jni::constructor<String> constructor{ *this };
    END_KLASS_DEF()
}