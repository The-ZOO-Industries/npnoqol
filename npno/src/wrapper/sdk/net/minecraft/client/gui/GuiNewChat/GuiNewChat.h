#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

#include "../../src/wrapper/sdk/net/minecraft/client/gui/ChatLine/ChatLine.h"

class GuiNewChat final : public JavaClass
{
public:
	explicit GuiNewChat(const jobject instance);

	virtual ~GuiNewChat() override;

	[[nodiscard]] std::vector<std::unique_ptr<ChatLine>> GetChatLines() const;

	void RefreshChat() const;
	void DeleteChatLine(const I32 id) const;
};

namespace maps
{
    BEGIN_KLASS_DEF(GuiNewChat, "net/minecraft/client/gui/GuiNewChat")
        jni::field<List, "chatLines"> chatLines{ *this };
        jni::method<void, "refreshChat"> refreshChat{ *this };
        jni::method<void, "deleteChatLine", jni::NOT_STATIC, jint> deleteChatLine{ *this };
    END_KLASS_DEF()
}