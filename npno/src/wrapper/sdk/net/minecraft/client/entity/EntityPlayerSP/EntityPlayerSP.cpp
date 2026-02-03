#include "EntityPlayerSP.h"

EntityPlayerSP::EntityPlayerSP(const jobject instance)
    : EntityPlayer(instance)
{

}

EntityPlayerSP::~EntityPlayerSP() = default;

std::unique_ptr<NetHandlerPlayClient> EntityPlayerSP::GetSendQueue() const 
{
    jni::frame f;

    return std::make_unique<NetHandlerPlayClient>(jni::make_global(maps::EntityPlayerSP(this->instance).sendQueue.get()));
}

void EntityPlayerSP::SendChatMessage(const std::string& message) const
{
    jni::frame f;

    maps::EntityPlayerSP(this->instance).sendChatMessage.call(JavaUtil::StringToJString(JavaUtil::FixString(message)));
}