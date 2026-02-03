#include "EntityPlayerSP.h"

EntityPlayerSP::EntityPlayerSP(const jobject instance)
    : EntityPlayer(instance)
{

}

EntityPlayerSP::~EntityPlayerSP() = default;

std::unique_ptr<NetHandlerPlayClient> EntityPlayerSP::GetSendQueue() const
{
    jni::frame f;

    return std::make_unique<NetHandlerPlayClient>(jobject(maps::NetHandlerPlayClient(maps::EntityPlayerSP(this->instance).sendQueue.get(), true)));
}

void EntityPlayerSP::SendChatMessage(const std::string& message) const
{
    jni::frame f;

    maps::String jmsg((jstring)JavaUtil::StringToJString(JavaUtil::FixString(message)));
    maps::EntityPlayerSP(this->instance).sendChatMessage.call(jmsg);
}