#include "ChatComponentText.h"

ChatComponentText::ChatComponentText(const jobject instance)
    : IChatComponent(instance)
{

}

ChatComponentText::ChatComponentText(const std::string& text)
    : IChatComponent(nullptr)
{
    jni::frame f;

    maps::String jTextStr((jstring)JavaUtil::StringToJString(JavaUtil::FixString(text)));

    maps::ChatComponentText newObj = maps::ChatComponentText::new_object(&maps::ChatComponentText_members::constructor, jTextStr);

    this->instance = Jvm::env->NewGlobalRef(jobject(newObj));
}

ChatComponentText::~ChatComponentText() = default;