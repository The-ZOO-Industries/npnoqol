#include "ChatComponentText.h"

ChatComponentText::ChatComponentText(const jobject instance)
    : IChatComponent(instance)
{

}

ChatComponentText::ChatComponentText(const std::string& text)
    : IChatComponent(nullptr)
{
    jni::frame f;

    this->instance = Jvm::env->NewGlobalRef(static_cast<jobject>(maps::ChatComponentText::new_object(&maps::ChatComponentText::constructor, JavaUtil::StringToJString(JavaUtil::FixString(text)))));
}

ChatComponentText::~ChatComponentText() = default;