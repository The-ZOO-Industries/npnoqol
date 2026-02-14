#include "ChatComponentText.h"

ChatComponentText::ChatComponentText(maps::ChatComponentText instance)
    : IChatComponent(maps::IChatComponent(instance.object_instance, instance.is_global()))
{

}

ChatComponentText::ChatComponentText(const std::string& text)
    : IChatComponent(maps::IChatComponent(nullptr))
{
    jstring jText = JavaUtil::StringToJString(JavaUtil::FixString(text));
    maps::String textStr{ jText };

    maps::ChatComponentText newObj = maps::ChatComponentText::new_object(&maps::ChatComponentText_members::constructor, textStr);

    this->instance = maps::Object{ newObj.object_instance, true };
}

ChatComponentText::~ChatComponentText() = default;