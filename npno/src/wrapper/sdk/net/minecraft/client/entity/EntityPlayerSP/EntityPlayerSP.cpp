#include "EntityPlayerSP.h"

EntityPlayerSP::EntityPlayerSP(maps::EntityPlayerSP instance)
    : EntityPlayer(maps::EntityPlayer(instance.object_instance, instance.is_global()))
{

}

EntityPlayerSP::~EntityPlayerSP() = default;

std::unique_ptr<NetHandlerPlayClient> EntityPlayerSP::GetSendQueue() const
{
    maps::NetHandlerPlayClient sendQueue = maps::EntityPlayerSP(this->instance.object_instance).sendQueue.get();
    maps::NetHandlerPlayClient globalSendQueue{ sendQueue.object_instance, true };
    return std::make_unique<NetHandlerPlayClient>(globalSendQueue);
}

void EntityPlayerSP::SendChatMessage(const std::string& message) const
{
    jstring jmsg = JavaUtil::StringToJString(JavaUtil::FixString(message));
    maps::String msgStr{ jmsg };
    maps::EntityPlayerSP(this->instance.object_instance).sendChatMessage.call(msgStr);
}